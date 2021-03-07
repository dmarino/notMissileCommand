/*
	Copyright (C) Daniela Marino
	
	Singleton template 
	I know is a bad practice to put the implementation in the header file but i couldn't make it work otherwise sorry :(
*/

template<typename T>

class Singleton
{

public:

	static T* mInstance;

	static void createInstance() {

		if (mInstance == nullptr) {
			mInstance = new T();
		}
	}

	static void destroyInstance() {

		delete mInstance;
		mInstance = nullptr;
	}

	static T* getInstance() {

		return mInstance;
	}

protected:

	Singleton() {}
	Singleton(const Singleton& other) = delete;
	Singleton& operator=(const Singleton& other) = delete;

};
