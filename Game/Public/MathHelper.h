#pragma once

#include "Engine/Public/EngineTypes.h"
#include<math.h>

//class that handles some vector math
class MathHelper{

public:
	MathHelper() {}
	~MathHelper(){}

	float dotProduct(exVector2& one, exVector2& two) {

		return (one.x * two.x) + (one.y * two.y);
	}

	void vectorScale(exVector2& out, exVector2& in, float scale) {
		out.x = in.x * scale;
		out.y = in.y * scale;
	}

	void vectorRest(exVector2& res, exVector2& one, exVector2& two) {
		res.x = one.x - two.x;
		res.y = one.y - two.y;
	}

	void vectorAdd(exVector2& res, exVector2& one, exVector2& two) {
		res.x = one.x + two.x;
		res.y = one.y + two.y;
	}


	void reflection(exVector2& res, exVector2& vector, exVector2& normal) {

		float dot = dotProduct(vector, normal);

		exVector2 multiplied;
		vectorScale(multiplied, normal, 2 * dot);

		vectorRest(res, vector, multiplied);
	}

	void normilizeVector(exVector2& res, exVector2& vector) {

		float magnitude = giveMagnitude(vector);
		res.x = res.x / magnitude;
		res.y = res.y / magnitude;
	}

	float giveMagnitude(exVector2& vector) {
		return sqrt((vector.x * vector.x) + (vector.y * vector.y));
	}

	int compareVectorsLenght(exVector2& one, exVector2& two) {
		
		float magOne = giveMagnitude(one);
		float magTwo = giveMagnitude(two);

		if (magOne < magTwo) {
			return -1;
		}
		else if (magOne > magTwo) {
			return 1;
		}

		return 0;
	}

};