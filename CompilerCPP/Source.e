block1 {
	.int8 a;
	block2 {
		.int8 b;
		.end block1;
		block3 {
			.int8 b;
			.begin block2;
			.int8 c;
		}
		.int8 c;
	}
	.int8 d;
}

