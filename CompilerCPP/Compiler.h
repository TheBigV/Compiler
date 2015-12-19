#pragma once


#include <string>
#include <vector>
#include <list>
#include <map>


namespace LangE
{
	typedef signed __int8					sint8;
	typedef unsigned __int8					uint8;
	typedef signed __int16					sint16;
	typedef unsigned __int16				uint16;
	typedef signed __int32					sint32;
	typedef unsigned __int32				uint32;
	typedef signed __int64					sint64;
	typedef unsigned __int64				uint64;

	struct Token;
	namespace Tokens
	{
		struct Semicolon;
		struct Indetifier;
	}

	struct Instruction;
	namespace Instructions
	{
		struct Variable;
		struct Definition;
		struct Keyword;
		namespace Keywords
		{
			struct If;
		}
	}

	struct Lexer;
	struct Parser;
	struct Compiler;

	struct DataType
	{
		const std::string name;
		const uint32 size;

		DataType(const std::string& name_, uint32 size_);
	};

	struct Token
	{
		enum struct Type
		{
			None,
			Semicolon,
			Literal,
			Indetifier,
			Keyword
		};

		virtual Token::Type GetTokenType() const = 0;
		virtual Instruction* Parse(Parser* parser) const;
		virtual Instructions::Variable* ParseVariables(Parser* parser) const;
	};
	namespace Tokens
	{
		struct Semicolon:
		public Token
		{
			virtual Token::Type GetTokenType() const override;
		};
		struct Literal:
			public Token
		{
			const std::string name;

			Literal(std::string name_);

			virtual Token::Type GetTokenType() const override;
			//virtual Instruction* Parse(Parser* parser) const override;
			//virtual Instructions::Variable* ParseVariables(Parser* parser) const override;
		};
		struct Indetifier:
			public Token
		{
			const std::string name;

			Indetifier(std::string name_);

			virtual Token::Type GetTokenType() const override;
			virtual Instruction* Parse(Parser* parser) const override;
			virtual Instructions::Variable* ParseVariables(Parser* parser) const override;
		};
		struct Keyword:
			public Token
		{
			enum struct Type
			{
				None,
				If
			};

			virtual Token::Type GetTokenType() const override;
			virtual Keyword::Type GetKeywordType() const = 0;
		};
		namespace Keywords
		{
			struct If:
				public Keyword
			{
				virtual Keyword::Type GetKeywordType() const override;
				virtual Instruction* Parse(Parser* parser) const override;
				virtual Instructions::Variable* ParseVariables(Parser* parser) const override;
			};
		}
	}

	struct Instruction
	{
		enum struct Type
		{
			None,
			Variable,
			Definition,
			Keyword
		};

		virtual Instruction::Type GetInstructionType() const = 0;
		virtual std::vector<uint8> Compile(Compiler* compiler) const;
	};
	namespace Instructions
	{
		struct Variable:
			public Instruction
		{
			DataType*const type;
			const std::string name;
			uint32 stackOffset;

			Variable(DataType* type_,std::string name_);

			virtual Instruction::Type GetInstructionType() const override;
			virtual std::vector<uint8> Compile(Compiler* compiler) const override;
		};
		struct Definition:
			public Instruction
		{
			Variable* const variable;
			const void* const value;

			Definition(Variable* variable_,void* value_ = nullptr);

			virtual Instruction::Type GetInstructionType() const override;
			virtual std::vector<uint8> Compile(Compiler* compiler) const override;
		};
		struct Keyword:
			public Instruction
		{
			enum struct Type
			{
				None,
				If
			};

			virtual Instruction::Type GetInstructionType() const override;
			virtual Keyword::Type GetKeywordType() const = 0;
		};
		namespace Keywords
		{
			struct If:
				public Keyword
			{
				Variable* condition;
				Instruction* positive;
				Instruction* negative;

				If(Instructions::Variable* condition_,Instruction* positive_,Instruction* negative_);

				virtual Keyword::Type GetKeywordType() const override;
				virtual std::vector<uint8> Compile(Compiler* compiler) const override;
			};
		}
	};

	struct Lexer
	{
		virtual std::vector<Token*> Process(const std::string& source);
	};
	struct Parser
	{
		static std::list<DataType*> basicTypes;

		size_t pos;
		std::vector<Token*>* tokens;

		std::map<std::string,DataType*> types;
		std::map<std::string,Instructions::Variable*> variables;

		Parser();

		virtual std::vector<Instruction*> Process(std::vector<Token*> tokens);
		virtual void AddVariable(Instructions::Variable* variable);
		virtual DataType* SearchDataType(const std::string& name);
		virtual Instructions::Variable* SearchVariable(const std::string& name);
	};
	struct Compiler
	{
		uint32 stackOffset;

#pragma region Commands
		static inline uint32 Inverse(uint32 i)
		{
			return ~i + 1;
		}
#pragma region Nop
		virtual std::vector<uint8> NOP() = 0; // No operation
#pragma endregion
#pragma region Convertion
		virtual std::vector<uint8> CBW() = 0; // byte -> word
		virtual std::vector<uint8> CWD() = 0; // word -> dword
		virtual std::vector<uint8> CDQ() = 0; // dword -> qword
#pragma endregion
#pragma region Push/Pop
		virtual std::vector<uint8> Push8(uint8 value) = 0;
#pragma endregion
#pragma region Jump
		virtual std::vector<uint8> JZ32(uint32 value) = 0; // jump if zero main+int32
		virtual std::vector<uint8> JNZ32(uint32 value) = 0; // jump if not zero main+int32
		virtual std::vector<uint8> Jump32(uint32 value) = 0; // jump main+int32
#pragma endregion
#pragma region Mov
#pragma region ETX, 32
		virtual std::vector<uint8> Mov_EAX_32(uint32 value) = 0; // mov eax, 0x08040201
#pragma endregion
#pragma region ETX, [ETX + 32]
		virtual std::vector<uint8> Mov_AL_LOC_ESPplus32(uint32 value) = 0; // mov al, [esp + 0x01020408]
		virtual std::vector<uint8> Mov_EAX_LOC_ESPplus32(uint32 value) = 0; // mov eax, [esp + 0x01020408]
#pragma endregion
#pragma endregion
#pragma region Lea
		virtual std::vector<uint8> Lea_ESP_LocESPPlus8(uint8 value) = 0; // lea esp, [esp + 0x00]
		virtual std::vector<uint8> Lea_ESP_LocESPPlus32(uint32 value) = 0; // lea esp, [esp + 0x08040201]
#pragma endregion
#pragma endregion

		virtual std::vector<uint8> Process(std::vector<Instruction*> instructions) = 0;
	};
	namespace Compilers
	{
		struct ASM86:
			public Compiler
		{
#pragma region Commands
#pragma region Nop
			virtual std::vector<uint8> NOP() override;
#pragma endregion
#pragma region Convertion
			virtual std::vector<uint8> CBW() override;
			virtual std::vector<uint8> CWD() override;
			virtual std::vector<uint8> CDQ() override;
#pragma endregion
#pragma region Push/Pop
			virtual std::vector<uint8> Push8(uint8 value) override;
#pragma endregion
#pragma region Jump
			virtual std::vector<uint8> JZ32(uint32 value) override;
			virtual std::vector<uint8> JNZ32(uint32 value) override;
			virtual std::vector<uint8> Jump32(uint32 value) override;
#pragma endregion
#pragma region Mov
#pragma region ETX, 32
			virtual std::vector<uint8> Mov_EAX_32(uint32 value) override;
#pragma endregion
#pragma region ETX, [ETX + 32]
			virtual std::vector<uint8> Mov_AL_LOC_ESPplus32(uint32 value) override;
			virtual std::vector<uint8> Mov_EAX_LOC_ESPplus32(uint32 value) override;
#pragma endregion
#pragma endregion
#pragma region Lea
			virtual std::vector<uint8> Lea_ESP_LocESPPlus8(uint8 value) override;
			virtual std::vector<uint8> Lea_ESP_LocESPPlus32(uint32 value) override;
#pragma endregion
#pragma endregion
			virtual std::vector<uint8> Process(std::vector<Instruction*> instructions) override;
		};
	}

	static bool isDigit(char c);
	static bool isLetter(char c);
	static bool isWhiteSpace(char c);

	std::vector<uint8> Compile(const std::string& source);
};































