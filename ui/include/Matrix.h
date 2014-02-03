#pragma once

class MatrixDelegate;

class AK_API Matrix
{
public:
	Matrix();
	~Matrix();

public:
	MatrixDelegate* _matrixDelegate;
};