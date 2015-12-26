#include "Compiler.h"


#pragma region LangE
#pragma region DataType
LangE::DataType::DataType(const std::string& name_, uint32 size_):
	name(name_),
	size(size_)
{
}
#pragma endregion
#pragma region Tokens
#pragma region Token
LangE::Instruction*											LangE::Token::Parse(Parser* parser)
{
	throw std::exception("");
}
LangE::Instructions::Variable*								LangE::Token::ParseVariables(Parser* parser)
{
	++parser->pos;
	return nullptr;
}
#pragma endregion
#pragma region Block
LangE::Token::Type							LangE::Tokens::Block::GetTokenType() const
{
	return Token::Type::Block;
}
#pragma endregion
#pragma region Blocks
#pragma region Figured
LangE::Tokens::Block::Type					LangE::Tokens::Blocks::Figured::GetBlockType() const
{
	return Block::Type::Figured;
}
#pragma endregion
#pragma region Figureds
#pragma region Begin
LangE::Tokens::Blocks::Figured::Type		LangE::Tokens::Blocks::Figureds::Begin::GetFiguredType() const
{
	return Figured::Type::Begin;
}
LangE::Instruction*							LangE::Tokens::Blocks::Figureds::Begin::Parse(Parser* parser)
{
	auto &pos = parser->pos;
	auto &tokens = parser->tokens;

	if(block)
	{
		++pos;

		parser->blocks.push_back(block);

		while(pos < tokens->size())
		{
			auto &token = (*tokens)[pos];

			if(token->GetTokenType() == Token::Type::Block)
			{
				auto tokenBlock = (Tokens::Block*)(*tokens)[pos];
				if(tokenBlock->GetBlockType() == Tokens::Block::Type::Figured)
				{
					auto tokenBlockFigured = (Tokens::Blocks::Figured*)tokenBlock;
					if(tokenBlockFigured->GetFiguredType() == Tokens::Blocks::Figured::Type::End)
					{
						++pos;
						if(parser->blocks.size() > 0 && parser->blocks.back() == block)
						{
							parser->blocks.pop_back();
							return block;
						}
						else
						{
							throw std::exception("");
						}
					}
				}
			}

			auto instruction = token->Parse(parser);
			instruction = Tokens::Keywords::Loop::Parse(parser,instruction);
			block->instructions.push_back(instruction);
		}
	}
	else
	{
		throw std::exception("");
	}

	throw std::exception("");
}
LangE::Instructions::Variable*				LangE::Tokens::Blocks::Figureds::Begin::ParseVariables(Parser* parser)
{
	auto &pos = parser->pos;
	auto &tokens = parser->tokens;

	if(block)
	{
		throw std::exception("");
	}
	else
	{
		block = new Instructions::Block(name);
		parser->blocks.push_back(block);
	}

	++pos;
	while(pos < tokens->size())
	{
		auto &token = (*tokens)[pos];

		if(token->GetTokenType() == Token::Type::Block)
		{
			auto tokenBlock = (Tokens::Block*)(*tokens)[pos];
			if(tokenBlock->GetBlockType() == Tokens::Block::Type::Figured)
			{
				auto tokenBlockFigured = (Tokens::Blocks::Figured*)tokenBlock;
				if(tokenBlockFigured->GetFiguredType() == Tokens::Blocks::Figured::Type::End)
				{
					++pos;
					if(parser->blocks.size() > 0 && parser->blocks.back() == block)
					{
						parser->blocks.pop_back();
					}
					else
					{
						throw std::exception("");
					}
					return nullptr;
				}
			}
		}

		parser->AddVariable(token->ParseVariables(parser));
	}

	throw std::exception("");
}
#pragma endregion
#pragma region End
LangE::Tokens::Blocks::Figured::Type		LangE::Tokens::Blocks::Figureds::End::GetFiguredType() const
{
	return Figured::Type::End;
}
#pragma endregion
#pragma endregion
#pragma region Round
LangE::Tokens::Block::Type					LangE::Tokens::Blocks::Round::GetBlockType() const
{
	return Block::Type::Round;
}
#pragma endregion
#pragma region Rounds
#pragma region Begin
LangE::Tokens::Blocks::Round::Type			LangE::Tokens::Blocks::Rounds::Begin::GetRoundType() const
{
	return Round::Type::Begin;
}
#pragma endregion
#pragma region End
LangE::Tokens::Blocks::Round::Type			LangE::Tokens::Blocks::Rounds::End::GetRoundType() const
{
	return Round::Type::End;
}
#pragma endregion
#pragma endregion
#pragma region Squared
LangE::Tokens::Block::Type					LangE::Tokens::Blocks::Squared::GetBlockType() const
{
	return Block::Type::Squared;
}
#pragma endregion
#pragma region Squareds
#pragma region Begin
LangE::Tokens::Blocks::Squared::Type		LangE::Tokens::Blocks::Squareds::Begin::GetSquaredType() const
{
	return Squared::Type::Begin;
}
#pragma endregion
#pragma region End
LangE::Tokens::Blocks::Squared::Type		LangE::Tokens::Blocks::Squareds::End::GetSquaredType() const
{
	return Squared::Type::End;
}
#pragma endregion
#pragma endregion
#pragma region Angled
LangE::Tokens::Block::Type					LangE::Tokens::Blocks::Angled::GetBlockType() const
{
	return Block::Type::Angled;
}
#pragma endregion
#pragma region Angleds
#pragma region Begin
LangE::Tokens::Blocks::Angled::Type			LangE::Tokens::Blocks::Angleds::Begin::GetAngledType() const
{
	return Angled::Type::Begin;
}
#pragma endregion
#pragma region End
LangE::Tokens::Blocks::Angled::Type			LangE::Tokens::Blocks::Angleds::End::GetAngledType() const
{
	return Angled::Type::End;
}
#pragma endregion
#pragma endregion
#pragma endregion
#pragma region Semicolon
LangE::Token::Type											LangE::Tokens::Semicolon::GetTokenType() const
{
	return Token::Type::Semicolon;
}
#pragma endregion
#pragma region Literal
LangE::Tokens::Literal::Literal(std::string name_):
	name(name_)
{
}
LangE::Token::Type											LangE::Tokens::Literal::GetTokenType() const
{
	return Token::Type::Literal;
}
#pragma endregion
#pragma region Indetifier
LangE::Tokens::Indetifier::Indetifier(std::string name_):
	name(name_)
{
}
LangE::Token::Type											LangE::Tokens::Indetifier::GetTokenType() const
{
	return Token::Type::Indetifier;
}
LangE::Instruction*											LangE::Tokens::Indetifier::Parse(Parser* parser)
{
	auto &pos = parser->pos;
	auto &tokens = *parser->tokens;

	if(pos + 1 < tokens.size() && tokens[pos + 1]->GetTokenType() == Token::Type::Block)
	{
		auto tokenBlock = (Tokens::Block*)tokens[pos + 1];
		if
		(
			(tokenBlock->GetBlockType() == Tokens::Block::Type::Figured && ((Tokens::Blocks::Figured*)tokenBlock)->GetFiguredType() == Tokens::Blocks::Figured::Type::Begin) ||
			(tokenBlock->GetBlockType() == Tokens::Block::Type::Round && ((Tokens::Blocks::Round*)tokenBlock)->GetRoundType() == Tokens::Blocks::Round::Type::Begin) ||
			(tokenBlock->GetBlockType() == Tokens::Block::Type::Squared && ((Tokens::Blocks::Squared*)tokenBlock)->GetSquaredType() == Tokens::Blocks::Squared::Type::Begin) ||
			(tokenBlock->GetBlockType() == Tokens::Block::Type::Angled && ((Tokens::Blocks::Angled*)tokenBlock)->GetAngledType() == Tokens::Blocks::Angled::Type::Begin)
		)
		{
			++pos;
			auto instruction = tokens[pos]->Parse(parser);
			if(instruction && instruction->GetInstructionType() == Instruction::Type::Block)
			{
				auto block = (Instructions::Block*)instruction;
				return block;
			}
			else
			{
				throw std::exception("");
			}
		}
	}

	auto dataType = parser->SearchDataType(name);
	if(dataType)
	{
		++parser->pos;
		if(parser->pos < parser->tokens->size())
		{
			if((*parser->tokens)[parser->pos]->GetTokenType() == Token::Type::Indetifier)
			{
				auto tokenVariable = (Tokens::Indetifier*)(*parser->tokens)[parser->pos];
				++parser->pos;
				if(parser->pos < parser->tokens->size())
				{
					auto definition = [&]()
					{
						auto variableName = tokenVariable->name;
						auto variable = parser->SearchVariable(variableName);

						if((*parser->tokens)[parser->pos]->GetTokenType() == Token::Type::Semicolon)
						{
							auto tokenSemicolon = (Tokens::Semicolon*)(*parser->tokens)[parser->pos];
							++parser->pos;

							if(variable)
							{
								auto definition = new Instructions::Definition(variable);
								return definition;
							}
							else
							{
								throw std::exception("");
							}
						}
						if((*parser->tokens)[parser->pos]->GetTokenType() == Token::Type::Literal)
						{
							auto tokenLiteral = (Tokens::Literal*)(*parser->tokens)[parser->pos];
							++parser->pos;

							if((*parser->tokens)[parser->pos]->GetTokenType() == Token::Type::Semicolon)
							{
								auto tokenSemicolon = (Tokens::Semicolon*)(*parser->tokens)[parser->pos];
								++parser->pos;

								auto definition = [&]()
								{
									if(variable->type->name == ".int8")
									{
										try
										{
											auto value = new uint8((uint8)std::strtol(tokenLiteral->name.c_str(),nullptr,10));
											auto definition = new Instructions::Definition(variable,value);
											return definition;
										}
										catch(...)
										{
											throw std::exception("");
										}
									}
									throw std::exception("");
								}();

								return definition;
							}
							else
							{
								throw std::exception("");
							}
							/*auto tokenSemicolon = (Tokens::Semicolon*)(*parser->tokens)[parser->pos];
							++parser->pos;

							auto variableName = tokenVariable->name;
							auto variable = parser->SearchVariable(variableName);

							if(variable)
							{
								auto definition = new Instructions::Definition(variable);

								return definition;
							}
							else
							{
								throw std::exception("");
							}*/
						}
						throw std::exception("");
					}();
					return definition;
				}
				else
				{
					throw std::exception("");
				}
			}
			else
			{
				throw std::exception("");
			}
		}
		else
		{
			throw std::exception("");
		}
	}
	else
	{
		auto variable = parser->SearchVariable(name);
		if(variable)
		{
			++parser->pos;
			if(parser->pos < parser->tokens->size())
			{
				if((*parser->tokens)[parser->pos]->GetTokenType() == Token::Type::Semicolon)
				{
					auto tokenSemicolon = (Tokens::Semicolon*)(*parser->tokens)[parser->pos];
					++parser->pos;

					/*auto leaveCondition = Tokens::Keywords::Loop::TryParse(parser);
					if(leaveCondition)
					{
						auto instructionCycle = new Instructions::Keywords::Cycle(nullptr,leaveCondition,variable);
						return instructionCycle;
					}
					else
					{
						return variable;
					}*/
					return variable;
				}
				else
				{
					throw std::exception("");
				}
			}
			else
			{
				throw std::exception("");
			}
		}
		else
		{
			throw std::exception("");
		}
	}
}
LangE::Instructions::Variable*								LangE::Tokens::Indetifier::ParseVariables(Parser* parser) 
{
	auto &pos = parser->pos;
	auto &tokens = *parser->tokens;

	if(pos + 1 < tokens.size() && tokens[pos + 1]->GetTokenType() == Token::Type::Block)
	{
		auto tokenBlock = (Tokens::Block*)tokens[pos + 1];
		if
			(
			(tokenBlock->GetBlockType() == Tokens::Block::Type::Figured && ((Tokens::Blocks::Figured*)tokenBlock)->GetFiguredType() == Tokens::Blocks::Figured::Type::Begin) ||
			(tokenBlock->GetBlockType() == Tokens::Block::Type::Round && ((Tokens::Blocks::Round*)tokenBlock)->GetRoundType() == Tokens::Blocks::Round::Type::Begin) ||
			(tokenBlock->GetBlockType() == Tokens::Block::Type::Squared && ((Tokens::Blocks::Squared*)tokenBlock)->GetSquaredType() == Tokens::Blocks::Squared::Type::Begin) ||
			(tokenBlock->GetBlockType() == Tokens::Block::Type::Angled && ((Tokens::Blocks::Angled*)tokenBlock)->GetAngledType() == Tokens::Blocks::Angled::Type::Begin)
			)
		{
			tokenBlock->name = name;
			auto variable = tokens[++pos]->ParseVariables(parser);
			return variable;
		}
	}

	auto dataType = parser->SearchDataType(name);
	if(dataType)
	{
		++pos;
		if(pos < tokens.size())
		{
			if(tokens[pos]->GetTokenType() == Token::Type::Indetifier)
			{
				auto tokenVariable = (Tokens::Indetifier*)tokens[pos];
				++pos;
				if(pos < tokens.size())
				{
					if(tokens[pos]->GetTokenType() == Token::Type::Semicolon)
					{
						auto tokenSemicolon = (Tokens::Semicolon*)tokens[pos];
						++pos;

						auto variable = new Instructions::Variable(dataType, tokenVariable->name);

						return variable;
					}
					else
					{
						return nullptr;
					}
				}
				else
				{
					return nullptr;
				}
			}
			else
			{
				return nullptr;

			}
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		++pos;
		if(pos < tokens.size() && tokens[pos]->GetTokenType() == Token::Type::Semicolon)
		{
			++pos;
		}
		return nullptr;
	}
}
#pragma endregion
#pragma region Keywords
#pragma region Keyword
LangE::Token::Type											LangE::Tokens::Keyword::GetTokenType() const
{
	return Token::Type::Keyword;
}
#pragma endregion
#pragma region If
LangE::Tokens::Keyword::Type									LangE::Tokens::Keywords::If::GetKeywordType() const
{
	return Keyword::Type::If;
}
LangE::Instruction*												LangE::Tokens::Keywords::If::Parse(Parser* parser)
{
	++parser->pos;
	if(parser->pos < parser->tokens->size())
	{
		auto condition = (*parser->tokens)[parser->pos]->Parse(parser);
		if(condition)
		{
			if(condition->GetInstructionType() == Instruction::Type::Variable)
			{
				auto conditionVariable = (Instructions::Variable*)condition;

				if(parser->pos < parser->tokens->size())
				{
					auto positive = (*parser->tokens)[parser->pos]->Parse(parser);
					if(positive)
					{
						if(parser->pos < parser->tokens->size())
						{
							auto tmpToken = (*parser->tokens)[parser->pos];
							if(tmpToken->GetTokenType() == Token::Type::Keyword)
							{
								auto tmpTokenKeyword = (Tokens::Keyword*)tmpToken;
								if(tmpTokenKeyword->GetKeywordType() == Tokens::Keyword::Type::Else)
								{
									auto tmpTokenKeywordElse = (Tokens::Keywords::Else*)tmpTokenKeyword;

									if(++parser->pos < parser->tokens->size())
									{
										auto negative = (*parser->tokens)[parser->pos]->Parse(parser);
										if(negative)
										{
											auto keywordIfElse = new Instructions::Keywords::If(conditionVariable,positive,negative);
											return keywordIfElse;
										}
										else
										{
											throw std::exception("");
										}
									}
									else
									{
										throw std::exception("");
									}
								}
							}
						}
						auto keywordIf = new Instructions::Keywords::If(conditionVariable,positive,nullptr);
						return keywordIf;
					}
					else
					{
						throw std::exception("[.if] Can't parse positive instruction");
					}
				}
				else
				{
					throw std::exception("[.if] There is no positive instruction");
				}
			}
			else
			{
				throw std::exception("[.if]Condition are not variable");
			}
		}
		else
		{
			throw std::exception("[.if] Can't parse condition");
		}
	}
	else
	{
		throw std::exception("[.if] There is no condition");
	}
}
LangE::Instructions::Variable*									LangE::Tokens::Keywords::If::ParseVariables(Parser* parser)
{
	++parser->pos;
	if(parser->pos < parser->tokens->size())
	{
		auto condition = (*parser->tokens)[parser->pos]->ParseVariables(parser);
		if(parser->pos < parser->tokens->size())
		{
			auto positive = (*parser->tokens)[parser->pos]->ParseVariables(parser);
		}
		else
		{
			throw std::exception("");
		}
		return nullptr;
	}
	else
	{
		throw std::exception("");
	}

	/*while(parser->pos < parser->tokens->size() && (*parser->tokens)[parser->pos]->GetTokenType() != Token::Type::Semicolon) ++parser->pos;
	if(parser->pos < parser->tokens->size())
	{
		++parser->pos;
		while(parser->pos < parser->tokens->size() && (*parser->tokens)[parser->pos]->GetTokenType() != Token::Type::Semicolon) ++parser->pos;
		return nullptr;
	}
	else
	{
		throw std::exception("");
	}*/
}
#pragma endregion
#pragma region Else
LangE::Tokens::Keyword::Type									LangE::Tokens::Keywords::Else::GetKeywordType() const
{
	return Keyword::Type::Else;
}
#pragma endregion
#pragma region Begin
LangE::Tokens::Keyword::Type									LangE::Tokens::Keywords::Begin::GetKeywordType() const
{
	return Keyword::Type::Begin;
}
LangE::Instruction*												LangE::Tokens::Keywords::Begin::Parse(Parser* parser)
{
	auto &pos = parser->pos;
	auto &tokens = *parser->tokens;

	if(++pos < tokens.size())
	{
		if(tokens[pos]->GetTokenType() == Token::Type::Semicolon)
		{
			++pos;

			if(!parser->blocks.empty())
			{
				auto block = parser->blocks.back();
				auto keywordBegin = new Instructions::Keywords::Begin(block);
				return keywordBegin;
			}
			else
			{
				throw std::exception("[.begin] can't find block");
			}
		}
		if(tokens[pos]->GetTokenType() == Token::Type::Indetifier)
		{
			auto indetifier = (Tokens::Indetifier*)tokens[pos];

			if(++pos < tokens.size() && tokens[pos]->GetTokenType() == Token::Type::Semicolon)
			{
				auto block = parser->SearchBlock(indetifier->name);
				if(block)
				{
					++pos;
					auto keywordBegin = new Instructions::Keywords::Begin(block);
					return keywordBegin;
				}
				else
				{
					throw std::exception("[.begin] can't find block");
				}
			}
			else
			{
				throw std::exception("[.begin] no semicolon ahead");
			}
		}
		throw std::exception("[.begin] no semicolon ahead");
	}
	else
	{
		throw std::exception("[.begin] no semicolon ahead");
	}
}
#pragma endregion
#pragma region End
LangE::Tokens::Keyword::Type									LangE::Tokens::Keywords::End::GetKeywordType() const
{
	return Keyword::Type::End;
}
LangE::Instruction*												LangE::Tokens::Keywords::End::Parse(Parser* parser)
{
	auto &pos = parser->pos;
	auto &tokens = *parser->tokens;

	if(++pos < tokens.size())
	{
		if(tokens[pos]->GetTokenType() == Token::Type::Semicolon)
		{
			++pos;

			if(!parser->blocks.empty())
			{
				auto block = parser->blocks.back();
				auto keywordEnd = new Instructions::Keywords::End(block);
				return keywordEnd;
			}
			else
			{
				throw std::exception("[.end] can't find block");
			}
		}
		if(tokens[pos]->GetTokenType() == Token::Type::Indetifier)
		{
			auto indetifier = (Tokens::Indetifier*)tokens[pos];

			if(++pos < tokens.size() && tokens[pos]->GetTokenType() == Token::Type::Semicolon)
			{
				auto block = parser->SearchBlock(indetifier->name);
				if(block)
				{
					++pos;
					auto keywordEnd = new Instructions::Keywords::End(block);
					return keywordEnd;
				}
				else
				{
					throw std::exception("[.end] can't find block");
				}
			}
			else
			{
				throw std::exception("[.end] no semicolon ahead");
			}
		}
		throw std::exception("[.end] no semicolon ahead");
	}
	else
	{
		throw std::exception("[.end] no semicolon ahead");
	}
}
#pragma endregion
#pragma region While
LangE::Tokens::Keyword::Type									LangE::Tokens::Keywords::While::GetKeywordType() const
{
	return Keyword::Type::While;
}
LangE::Instruction*												LangE::Tokens::Keywords::While::Parse(Parser* parser)
{
	auto &pos = parser->pos;
	auto &tokens = *parser->tokens;

	if(++pos < tokens.size())
	{
		auto entryTestCondition = tokens[pos]->Parse(parser);
		if(entryTestCondition->GetInstructionType() == Instruction::Type::Variable)
		{
			auto entryCondition = (Instructions::Variable*)entryTestCondition;
			if(pos < tokens.size())
			{
				auto instruction = tokens[pos]->Parse(parser);

				if(pos < tokens.size() && tokens[pos]->GetTokenType() == Token::Type::Keyword)
				{
					auto tokenKeyword = (Tokens::Keyword*)tokens[pos];
					if(tokenKeyword->GetKeywordType() == Tokens::Keyword::Type::Loop)
					{
						if(++pos < tokens.size())
						{
							auto leaveTestCondition = tokens[pos]->Parse(parser);
							if(entryTestCondition->GetInstructionType() == Instruction::Type::Variable)
							{
								auto leaveCondition = (Instructions::Variable*)leaveTestCondition;

								auto keywordCycle = new Instructions::Keywords::Cycle(entryCondition,leaveCondition,instruction);
								return keywordCycle;
							}
							else
							{
								throw std::exception("[.loop] leave condition are not variable");
							}
						}
						else
						{
							throw std::exception("[.loop] no instruction ahead");
						}
					}
				}

				auto keywordCycle = new Instructions::Keywords::Cycle(entryCondition,nullptr,instruction);
				return keywordCycle;
			}
			else
			{
				throw std::exception("[.while] no instruction ahead");
			}
		}
		else
		{
			throw std::exception("[.while] entry condition are not variable");
		}
	}
	else
	{
		throw std::exception("[.while] no condition ahead");
	}
}
LangE::Instructions::Variable*									LangE::Tokens::Keywords::While::ParseVariables(Parser* parser)
{
	auto &pos = parser->pos;
	auto &tokens = *parser->tokens;

	if(++pos < tokens.size())
	{
		auto condition = tokens[pos]->ParseVariables(parser);
		if(pos < tokens.size())
		{
			auto instruction = tokens[pos]->ParseVariables(parser);
			// loop todo
		}
		else
		{
			throw std::exception("[.while] no instruction ahead");
		}
		return nullptr;
	}
	else
	{
		throw std::exception("[.while] no condition ahead");
	}
}
#pragma endregion
#pragma region Loop
LangE::Instructions::Variable*									LangE::Tokens::Keywords::Loop::TryParse(Parser* parser)
{
	auto &pos = parser->pos;
	auto &tokens = *parser->tokens;

	if(pos < tokens.size() && tokens[pos]->GetTokenType() == Token::Type::Keyword)
	{
		auto tokenKeyword = (Tokens::Keyword*)tokens[pos];
		if(tokenKeyword->GetKeywordType() == Tokens::Keyword::Type::Loop)
		{			
			if(++pos < tokens.size())
			{
				auto instruction = tokens[pos]->Parse(parser);
				if(instruction->GetInstructionType() == Instruction::Type::Variable)
				{
					auto leaveCondition = (Instructions::Variable*)instruction;
					return leaveCondition;
				}
				else
				{
					throw std::exception("[.loop] leave condition are not variable");
				}
			}
			else
			{
				throw std::exception("[.loop] no leave condition ahead");
			}
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}
LangE::Instruction*												LangE::Tokens::Keywords::Loop::Parse(Parser* parser,Instruction* inputInstruction)
{
	auto &pos = parser->pos;
	auto &tokens = *parser->tokens;

	if(pos < tokens.size() && tokens[pos]->GetTokenType() == Token::Type::Keyword)
	{
		auto tokenKeyword = (Tokens::Keyword*)tokens[pos];
		if(tokenKeyword->GetKeywordType() == Tokens::Keyword::Type::Loop)
		{
			if(++pos < tokens.size())
			{
				auto instruction = tokens[pos]->Parse(parser);
				if(instruction->GetInstructionType() == Instruction::Type::Variable)
				{
					auto leaveCondition = (Instructions::Variable*)instruction;
					auto cycle = new Instructions::Keywords::Cycle(nullptr,leaveCondition,inputInstruction);
					return Parse(parser,cycle);
				}
				else
				{
					throw std::exception("[.loop] leave condition are not variable");
				}
			}
			else
			{
				throw std::exception("[.loop] no leave condition ahead");
			}
		}
		else
		{
			return inputInstruction;
		}
	}
	else
	{
		return inputInstruction;
	}
}
LangE::Tokens::Keyword::Type									LangE::Tokens::Keywords::Loop::GetKeywordType() const
{
	return Keyword::Type::Loop;
}
#pragma endregion
#pragma endregion
#pragma endregion
#pragma region Instructions
#pragma region Instruction
std::vector<LangE::uint8>										LangE::Instruction::Compile(Compiler* compiler)
{
	throw std::exception("");
}
#pragma endregion
#pragma region Block
LangE::Instructions::Block::Block(std::string name_):
	name(name_)
{

}
LangE::Instruction::Type										LangE::Instructions::Block::GetInstructionType() const
{
	return Instruction::Type::Block;
}
void LangE::Instructions::Block::_RecursiveBlockOffset(Instruction* instruction, std::size_t offset)
{
	if(instruction->GetInstructionType() == Instruction::Type::Block)
	{
		auto block = (Instructions::Block*)instruction;
		for(auto i : block->instructions)
		{
			_RecursiveBlockOffset(i,offset);
		}
	}
	if(instruction->GetInstructionType() == Instruction::Type::Keyword)
	{
		auto keyword = (Instructions::Keyword*)instruction;
		if(keyword->GetKeywordType() == Instructions::Keyword::Type::Begin)
		{
			auto keywordBegin = (Instructions::Keywords::End*)keyword;
			keywordBegin->beginJump += offset;
			keywordBegin->endJump += offset;
		}
		if(keyword->GetKeywordType() == Instructions::Keyword::Type::End)
		{
			auto keywordEnd = (Instructions::Keywords::End*)keyword;
			keywordEnd->beginJump += offset;
			keywordEnd->endJump += offset;
		}
	}
}
std::vector<LangE::uint8>										LangE::Instructions::Block::Compile(Compiler* compiler)
{
	std::vector<LangE::uint8> codes;

	stackOffset = compiler->stackOffset;

	for(auto instruction : instructions)
	{
		auto code = instruction->Compile(compiler);

		_RecursiveBlockOffset(instruction, codes.size());

		for(auto i : code) codes.push_back(i);
	}

	auto offset = compiler->stackOffset - stackOffset;
	if(offset)
	{
		auto code = compiler->Lea_ESP_LocESPPlus32(offset);
		for(auto i : code) codes.push_back(i);
		compiler->stackOffset = stackOffset;
	}

	for(auto i : jumpBegin)
	{
		auto jumpSize = -sint32(i->endJump);
		auto jumpCode = compiler->JMP32(jumpSize);

		for(std::size_t j = 0; j < jumpCode.size(); ++j)
		{
			codes[i->beginJump + j] = jumpCode[j];
		}
	}
	for(auto i : jumpEnd)
	{
		auto jumpSize = codes.size() - i->endJump;
		auto jumpCode = compiler->JMP32(jumpSize);

		for(std::size_t j = 0; j < jumpCode.size(); ++j)
		{
			codes[i->beginJump + j] = jumpCode[j];
		}
	}

	return move(codes);
}
#pragma endregion
#pragma region Variable
LangE::Instructions::Variable::Variable(DataType* type_,std::string name_):
	type(type_),
	name(name_)
{
}
LangE::Instruction::Type										LangE::Instructions::Variable::GetInstructionType() const
{
	return Type::Variable;
}
std::vector<LangE::uint8>										LangE::Instructions::Variable::Compile(Compiler* compiler)
{
	return move(compiler->NOP());
}
#pragma endregion
#pragma region Definition
LangE::Instructions::Definition::Definition(Variable* variable_,void* value_):
	variable(variable_),
	value(value_)
{
}
LangE::Instruction::Type										LangE::Instructions::Definition::GetInstructionType() const
{
	return Type::Definition;
}
std::vector<LangE::uint8>										LangE::Instructions::Definition::Compile(Compiler* compiler)
{
	compiler->stackOffset += variable->type->size;
	variable->stackOffset = compiler->stackOffset;
	return compiler->Lea_ESP_LocESPPlus32(Compiler::Inverse(variable->type->size));
	//return compiler->Push8(0x01);
	//return std::vector<uint8>{0x00};
}
#pragma endregion
#pragma region Keywords
#pragma region Keyword
LangE::Instruction::Type					LangE::Instructions::Keyword::GetInstructionType() const
{
	return Instruction::Type::Keyword;
}
#pragma endregion
#pragma region If
LangE::Instructions::Keywords::If::If(Instructions::Variable* condition_,Instruction* positive_,Instruction* negative_):
	condition(condition_),positive(positive_),negative(negative_)
{
}
LangE::Instructions::Keyword::Type								LangE::Instructions::Keywords::If::GetKeywordType() const
{
	return Keyword::Type::If;
}
std::vector<LangE::uint8>										LangE::Instructions::Keywords::If::Compile(Compiler* compiler)
{
	auto code = std::vector<uint8>{};

	auto conditionByteRelativeLocation = compiler->stackOffset - condition->stackOffset;
	auto conditionCode = compiler->Mov_AL_LOC_ESPplus32(Compiler::Inverse(conditionByteRelativeLocation));
	auto comparsionCode = compiler->CMP_AL_0();

	if(negative)
	{
		auto positiveCode = positive->Compile(compiler);

		auto negativeCode = negative->Compile(compiler);

		auto positiveJumpSize = negativeCode.size();
		auto positiveJumpCode = compiler->JMP32(positiveJumpSize);	// jump to the end of .else

		auto negativeJumpSize = positiveCode.size() + positiveJumpCode.size();
		auto negativeJumpCode = compiler->JZ32(negativeJumpSize); // jump to the .else


		for(auto i : conditionCode) code.push_back(i);
		for(auto i : comparsionCode) code.push_back(i);
		for(auto i : negativeJumpCode) code.push_back(i);
		for(auto i : positiveCode) code.push_back(i);
		for(auto i : positiveJumpCode) code.push_back(i);
		for(auto i : negativeCode) code.push_back(i);
	}
	else
	{
		auto positiveCode = positive->Compile(compiler);
		auto negativeJumpSize = positiveCode.size();

		auto negativeJumpCode = compiler->JZ32(negativeJumpSize); // jump to the end of .if

		for(auto i : conditionCode) code.push_back(i);
		for(auto i : comparsionCode) code.push_back(i);
		for(auto i : negativeJumpCode) code.push_back(i);
		for(auto i : positiveCode) code.push_back(i);
	}

	return code;
}
#pragma endregion
#pragma region Begin
LangE::Instructions::Keywords::Begin::Begin(Block* block_):
	block(block_)
{
	block->jumpBegin.push_back(this);
}
LangE::Instructions::Keyword::Type								LangE::Instructions::Keywords::Begin::GetKeywordType() const
{
	return Keyword::Type::Begin;
}
std::vector<LangE::uint8>										LangE::Instructions::Keywords::Begin::Compile(Compiler* compiler)
{
	auto code = std::vector<uint8>{};

	auto offset = compiler->stackOffset - block->stackOffset;
	if(offset > 0)
	{
		auto codeStackFree = compiler->Lea_ESP_LocESPPlus32(offset);
		for(auto i : codeStackFree) code.push_back(i);
	}

	auto jumpCode = compiler->JMP32(0);

	beginJump = code.size();
	for(auto i : jumpCode) code.push_back(i);
	endJump = code.size();

	return code;
}
#pragma endregion
#pragma region End
LangE::Instructions::Keywords::End::End(Block* block_):
	block(block_)
{
	block->jumpEnd.push_back(this);
}
LangE::Instructions::Keyword::Type								LangE::Instructions::Keywords::End::GetKeywordType() const
{
	return Keyword::Type::End;
}
std::vector<LangE::uint8>										LangE::Instructions::Keywords::End::Compile(Compiler* compiler)
{
	auto code = std::vector<uint8>{};

	auto offset = compiler->stackOffset - block->stackOffset;
	if(offset > 0)
	{
		auto codeStackFree = compiler->Lea_ESP_LocESPPlus32(offset);
		for(auto i : codeStackFree) code.push_back(i);
	}

	auto jumpCode = compiler->JMP32(0);
	
	beginJump = code.size();
	for(auto i : jumpCode) code.push_back(i);
	endJump = code.size();

	return code;
}
#pragma endregion
#pragma region Cycle
LangE::Instructions::Keywords::Cycle::Cycle(Variable* entryCondition_,Variable* leaveCondition_,Instruction* instruction_):
	entryCondition(entryCondition_),
	leaveCondition(leaveCondition_),
	instruction(instruction_)
{
}
LangE::Instructions::Keyword::Type			LangE::Instructions::Keywords::Cycle::GetKeywordType() const
{
	return Keyword::Type::Cycle;
}
std::vector<LangE::uint8>					LangE::Instructions::Keywords::Cycle::Compile(Compiler* compiler)
{
	auto code = std::vector<uint8>{};

	if(entryCondition)
	{
		if(leaveCondition)
		{
			auto cycleJumpIdleCode = compiler->JMP32(0);

			auto instructionCode = instruction->Compile(compiler);
			auto instructionSize = instructionCode.size();

			auto entryConditionByteRelativeLocation = compiler->stackOffset - entryCondition->stackOffset;
			auto entryConditionCode = compiler->Mov_AL_LOC_ESPplus32(Compiler::Inverse(entryConditionByteRelativeLocation));
			auto entryComparsionCode = compiler->CMP_AL_0();
			auto entryJumpIdleCode = compiler->JZ32(0);
			auto entrySize = entryConditionCode.size() + entryComparsionCode.size() + entryJumpIdleCode.size();

			auto leaveConditionByteRelativeLocation = compiler->stackOffset - leaveCondition->stackOffset;
			auto leaveConditionCode = compiler->Mov_AL_LOC_ESPplus32(Compiler::Inverse(leaveConditionByteRelativeLocation));
			auto leaveComparsionCode = compiler->CMP_AL_0();
			auto leaveJumpIdleCode = compiler->JZ32(0);
			auto leaveSize = leaveConditionCode.size() + leaveComparsionCode.size() + leaveJumpIdleCode.size();

			auto entryJumpCode = compiler->JZ32(instructionSize + leaveSize + cycleJumpIdleCode.size());
			auto leaveJumpCode = compiler->JZ32(cycleJumpIdleCode.size());

			auto cycleJumpCode = compiler->JMP32(-(sint32)(entrySize + instructionSize + leaveSize + cycleJumpIdleCode.size()));

			for(auto i : entryConditionCode) code.push_back(i);
			for(auto i : entryComparsionCode) code.push_back(i);
			for(auto i : entryJumpCode) code.push_back(i);
			for(auto i : instructionCode) code.push_back(i);
			for(auto i : leaveConditionCode) code.push_back(i);
			for(auto i : leaveComparsionCode) code.push_back(i);
			for(auto i : leaveJumpCode) code.push_back(i);
			for(auto i : cycleJumpCode) code.push_back(i);
		}
		else
		{
			auto cycleJumpGagCode = compiler->JMP32(0);

			auto entryConditionByteRelativeLocation = compiler->stackOffset - entryCondition->stackOffset;
			auto entryConditionCode = compiler->Mov_AL_LOC_ESPplus32(Compiler::Inverse(entryConditionByteRelativeLocation));
			auto entryComparsionCode = compiler->CMP_AL_0();

			auto instructionCode = instruction->Compile(compiler);
			auto instructionSize = instructionCode.size();

			auto entryJumpCode = compiler->JZ32(instructionSize + cycleJumpGagCode.size());

			auto entrySize = entryConditionCode.size() + entryComparsionCode.size() + entryJumpCode.size();

			auto cycleSize = entrySize + instructionSize + cycleJumpGagCode.size();
			auto cycleJumpCode = compiler->JMP32(-(sint32)cycleSize);

			for(auto i : entryConditionCode) code.push_back(i);
			for(auto i : entryComparsionCode) code.push_back(i);
			for(auto i : entryJumpCode) code.push_back(i);
			for(auto i : instructionCode) code.push_back(i);
			for(auto i : cycleJumpCode) code.push_back(i);
		}
	}
	else
	{
		if(leaveCondition)
		{
			auto instructionCode = instruction->Compile(compiler);

			auto leaveConditionByteRelativeLocation = compiler->stackOffset - leaveCondition->stackOffset;
			auto leaveConditionCode = compiler->Mov_AL_LOC_ESPplus32(Compiler::Inverse(leaveConditionByteRelativeLocation));
			auto leaveComparsionCode = compiler->CMP_AL_0();

			auto leaveJumpGagCode = compiler->JNZ32(0);

			auto cycleSize = instructionCode.size() + leaveConditionCode.size() + leaveComparsionCode.size() + leaveJumpGagCode.size();

			auto leaveJumpCode = compiler->JNZ32(-(sint32)cycleSize);

			for(auto i : instructionCode) code.push_back(i);
			for(auto i : leaveConditionCode) code.push_back(i);
			for(auto i : leaveComparsionCode) code.push_back(i);
			for(auto i : leaveJumpCode) code.push_back(i);
		}
		else
		{
			throw std::exception("sheeeit");
		}
	}

	return code;
}
#pragma endregion
#pragma endregion
#pragma endregion
#pragma region Lexer
std::vector<LangE::Token*>										LangE::Lexer::Process(const std::string& source)
{
	std::vector<Token*> tokens;

	for(size_t i = 0; i < source.size(); ++i)
	{
		auto symbol = source[i];

		switch(symbol)
		{
			case ' ': break;
			case '\r': break;
			case '\n': break;
			case '\t': break;
			case ';':
			{
				tokens.push_back(new Tokens::Semicolon);
			} break;
			case '.':
			{
				auto oi = i;
				++i;
				while(i < source.size() && (isLetter(source[i]) || isDigit(source[i]))) ++i;

				if(i < source.size())
				{
					if(isWhiteSpace(source[i]))
					{
						auto name = source.substr(oi,i - oi);

						([&]()
						{
							if([&name](){ for(auto i : Parser::basicTypes) if(i->name == name ) return true; return false; }())
							{
								tokens.push_back(new Tokens::Indetifier(name)); --i; return;
							}
							if(name == ".if")
							{
								tokens.push_back(new Tokens::Keywords::If); --i; return;
							}
							if(name == ".else")
							{
								tokens.push_back(new Tokens::Keywords::Else); --i; return;
							}
							if(name == ".begin")
							{
								tokens.push_back(new Tokens::Keywords::Begin); --i; return;
							}
							if(name == ".end")
							{
								tokens.push_back(new Tokens::Keywords::End); --i; return;
							}
							if(name == ".while")
							{
								tokens.push_back(new Tokens::Keywords::While); --i; return;
							}
							if(name == ".loop")
							{
								tokens.push_back(new Tokens::Keywords::Loop); --i; return;
							}
							throw std::exception("unsupported keyword type");
						})();
					}
					else
					{
					}
				}
				else
				{
					throw std::exception("?");
				}
			} break;
			case '{':
			{
				tokens.push_back(new Tokens::Blocks::Figureds::Begin);
			} break;
			case '}':
			{
				tokens.push_back(new Tokens::Blocks::Figureds::End);
			} break;
			case '(':
			{
				tokens.push_back(new Tokens::Blocks::Rounds::Begin);
			} break;
			case ')':
			{
				tokens.push_back(new Tokens::Blocks::Rounds::End);
			} break;
			case '[':
			{
				tokens.push_back(new Tokens::Blocks::Squareds::Begin);
			} break;
			case ']':
			{
				tokens.push_back(new Tokens::Blocks::Squareds::End);
			} break;
			case '<':
			{
				tokens.push_back(new Tokens::Blocks::Angleds::Begin);
			} break;
			case '>':
			{
				tokens.push_back(new Tokens::Blocks::Angleds::End);
			} break;
			case '\'':
			{
				auto oi = i;
				while(++i < source.size() && source[i] != '\'');

				if(source[i] == '\'')
				{
					try
					{
						//++i;
						auto valueString = source.substr(oi,i - oi);
						//auto name = std::strtol(.c_str(),nullptr,10);
						tokens.push_back(new Tokens::Literal(valueString));
					}
					catch(...)
					{
						throw std::exception("");
					}
				}
				else
				{
					throw std::exception("");
				}
			} break;
			default:
			{
				if(isLetter(symbol) || isDigit(symbol))
				{
					auto oi = i;
					++i;
					while(i < source.size() && (isLetter(source[i]) || isDigit(source[i]))) ++i;

					auto name = source.substr(oi,i - oi);
					tokens.push_back(new Tokens::Indetifier(name));
					--i;
				}
				else
				{
					throw std::exception("unsupported symbol type");
				}
			}
		}
	}

	return move(tokens);
}
#pragma endregion
#pragma region Parser
std::list<LangE::DataType*> LangE::Parser::basicTypes = {
	new LangE::DataType(".int8",1),
	new LangE::DataType(".int16",2),
	new LangE::DataType(".int32",4),
	new LangE::DataType(".int64",8),
	new LangE::DataType(".sint8",1),
	new LangE::DataType(".sint16",2),
	new LangE::DataType(".sint32",4),
	new LangE::DataType(".sint64",8),
	new LangE::DataType(".uint8",1),
	new LangE::DataType(".uint16",2),
	new LangE::DataType(".uint32",4),
	new LangE::DataType(".uint64",8)
};
LangE::Parser::Parser()
{
	for(auto i : basicTypes)
	{
		types.insert(std::pair<std::string,DataType*>(i->name,i));
	}
}
std::vector<LangE::Instruction*>								LangE::Parser::Process(std::vector<Token*> tokens_)
{
	std::vector<LangE::Instruction*> instructions;

	tokens = &tokens_;

	// types gather
	types;
	{
		//for(auto i : types) delete i.second;
		//types.clear();
	}

	// variables gather
	variables;
	{
		for(auto i : variables) delete i.second;
		variables.clear();

		pos = 0;
		while(pos < tokens->size())
		{
			auto token = (*tokens)[pos];
			AddVariable(token->ParseVariables(this));
		}
	}

	pos = 0;
	while(pos < tokens->size())
	{
		auto token = (*tokens)[pos];
		auto instruction = token->Parse(this);
		instruction = Tokens::Keywords::Loop::Parse(this,instruction);
		if(instruction) instructions.push_back(instruction);
	}

	return move(instructions);
}
void															LangE::Parser::AddVariable(Instructions::Variable* variable)
{	
	if(variable)
	{
		if(blocks.empty())
		{
			variables.insert(std::pair<std::string,Instructions::Variable*>(variable->name,variable));
		}
		else
		{
			blocks.back()->variables.insert(std::pair<std::string,Instructions::Variable*>(variable->name,variable));
		}
	}
}
LangE::DataType*												LangE::Parser::SearchDataType(const std::string& name)
{
	/*
	for(auto i = blocks.rbegin(); i != blocks.rend(); ++i)
	{
		auto &block = *i;
		auto dataTypeIt = block->types.find(name);
		if(dataTypeIt != block->types.end())
		{
			return (*dataTypeIt).second;
		}
	}

	auto dataTypeIt = types.find(name);
	if(dataTypeIt != types.end())
	{
		return (*dataTypeIt).second;
	}

	return nullptr;
	*/
	auto dataTypeIt = types.find(name);
	if(dataTypeIt != types.end())
	{
		return (*dataTypeIt).second;
	}
	else
	{
		return nullptr;
	}
}
LangE::Instructions::Variable*									LangE::Parser::SearchVariable(const std::string& name)
{
	for(auto i = blocks.rbegin(); i != blocks.rend(); ++i)
	{
		auto &block = *i;
		auto variableIt = block->variables.find(name);
		if(variableIt != block->variables.end())
		{
			return (*variableIt).second;
		}
	}

	auto variableIt = variables.find(name);
	if(variableIt != variables.end())
	{
		return (*variableIt).second;
	}

	return nullptr;

	/*auto variableIt = variables.find(name);
	if(variableIt != variables.end())
	{
		return (*variableIt).second;
	}
	else
	{
		return nullptr;
	}*/
}
LangE::Instructions::Block*										LangE::Parser::SearchBlock(const std::string& name)
{
	for(auto i = blocks.rbegin(); i != blocks.rend(); ++i)
	{
		auto block = *i;
		if(block->name == name) return block;
	}

	return nullptr;
}
#pragma endregion
#pragma region Compilers
#pragma region ASM86
#pragma region Commands
#pragma region Nop
std::vector<LangE::uint8>											LangE::Compilers::ASM86::NOP()
{
	return std::vector<uint8>{0x90};
}
#pragma endregion
#pragma region Convertion
std::vector<LangE::uint8>											LangE::Compilers::ASM86::CBW()
{
	return std::vector<uint8>{0x66,0x98};
}
std::vector<LangE::uint8>											LangE::Compilers::ASM86::CWD()
{
	return std::vector<uint8>{0x66,0x99};
}
std::vector<LangE::uint8>											LangE::Compilers::ASM86::CDQ()
{
	return std::vector<uint8>{0x99};
}
#pragma endregion
#pragma region Push/Pop
std::vector<LangE::uint8>										LangE::Compilers::ASM86::Push8(uint8 value)
{
	return std::vector<uint8>{0x6A, value};
}
#pragma endregion
#pragma region Compare
std::vector<LangE::uint8>											LangE::Compilers::ASM86::CMP_AL_0()
{
	return std::vector<uint8>{0x3C,0x00};
}
#pragma endregion
#pragma region Jump
std::vector<LangE::uint8>											LangE::Compilers::ASM86::JZ32(sint32 value)
{
	auto jmpSize = value;
	return std::vector<uint8>{0x0F,0x84,(uint8)(jmpSize << 0),(uint8)(jmpSize << 8),(uint8)(jmpSize << 16),(uint8)(jmpSize << 24)};
}
std::vector<LangE::uint8>											LangE::Compilers::ASM86::JNZ32(sint32 value)
{
	auto jmpSize = value;
	return std::vector<uint8>{0x0F,0x85,(uint8)(jmpSize >> 0),(uint8)(jmpSize >> 8),(uint8)(jmpSize >> 16),(uint8)(jmpSize >> 24)};
}
std::vector<LangE::uint8>											LangE::Compilers::ASM86::JMP32(sint32 value)
{
	auto jmpSize = value;
	return std::vector<uint8>{0xE9,(uint8)(jmpSize >> 0),(uint8)(jmpSize >> 8),(uint8)(jmpSize >> 16),(uint8)(jmpSize >> 24)};
}
#pragma endregion
#pragma region Mov
#pragma region ETX, 32
std::vector<LangE::uint8>											LangE::Compilers::ASM86::Mov_EAX_32(uint32 value)
{
	return std::vector<uint8>{0x8B,(uint8)(value >> 0),(uint8)(value >> 8),(uint8)(value >> 16),(uint8)(value >> 24)};
}
#pragma endregion
#pragma region ETX, [ETX + 32]
std::vector<LangE::uint8>											LangE::Compilers::ASM86::Mov_AL_LOC_ESPplus32(uint32 value)
{
	return std::vector<uint8>{0x8A,0x84,0x24,(uint8)(value >> 0),(uint8)(value >> 8),(uint8)(value >> 16),(uint8)(value >> 24)};
}
std::vector<LangE::uint8>											LangE::Compilers::ASM86::Mov_EAX_LOC_ESPplus32(uint32 value)
{
	return std::vector<uint8>{0x8B,0x84,0x24,(uint8)(value >> 0),(uint8)(value >> 8),(uint8)(value >> 16),(uint8)(value >> 24)};
}
#pragma endregion
#pragma endregion
#pragma region Lea
std::vector<LangE::uint8>										LangE::Compilers::ASM86::Lea_ESP_LocESPPlus8(uint8 value)
{
	return std::vector<uint8>{0x8D,0x64,0x24,value};
}
std::vector<LangE::uint8>										LangE::Compilers::ASM86::Lea_ESP_LocESPPlus32(uint32 value)
{
	return std::vector<uint8>{0x8D,0xA4,0x24,(uint8)(value >> 0),(uint8)(value >> 8),(uint8)(value >> 16),(uint8)(value >> 24)};
}
#pragma endregion
#pragma endregion
std::vector<LangE::uint8>											LangE::Compilers::ASM86::Process(std::vector<Instruction*> instructions)
{
	std::vector<LangE::uint8> codes;

	stackOffset = 0;

	for(auto instruction : instructions)
	{
		auto code = instruction->Compile(this);
		for(auto i : code) codes.push_back(i);
	}

	if(stackOffset > 0)
	{
		auto code = Lea_ESP_LocESPPlus32(stackOffset);
		for(auto i : code) codes.push_back(i);
	}

	return move(codes);
}
#pragma endregion
#pragma endregion
#pragma region Func
bool LangE::isDigit(char c)
{
	return isdigit(c) != 0;
}
bool LangE::isLetter(char c)
{
	return isalpha(c) != 0;
}
bool LangE::isWhiteSpace(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}
std::vector<LangE::uint8>										LangE::Compile(const std::string& source)
{
	Lexer lexer;
	Parser parser;
	Compilers::ASM86 compilerASM86;

	auto tokens = lexer.Process(source);
	auto instructions = parser.Process(tokens);
	auto code = compilerASM86.Process(instructions);

	return move(code);
}
#pragma endregion
#pragma endregion

#pragma region
#pragma endregion






























