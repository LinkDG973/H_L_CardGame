#pragma once
//====================================================================================
// NAME: Singleton.h
// DESC: Contains Singleton Class
// SOURCE : https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern
// AMENDED BY : Oliver Callaghan
//====================================================================================

// SUMMARY: Singleton Class, used to only allow a single instance of a specific class and allow that class to be accessed by other scripts.
template<class T> class Singleton {
public:
	Singleton() {
		assert(spSingleton == nullptr);
		spSingleton = static_cast<T*>(this);
	};
	virtual ~Singleton() {
		assert(spSingleton != nullptr);
		spSingleton = nullptr;
	}

	static T& getInstance() { // Returns the singleton instance of it's child class.
		assert(spSingleton != nullptr);
		return *spSingleton;
	}

private:
	static T* spSingleton;
	Singleton(Singleton const&) = delete;
	void operator=(Singleton const&) = delete;
};

template<typename T> T* Singleton<T>::spSingleton = 0;