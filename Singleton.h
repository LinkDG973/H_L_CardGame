#pragma once

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

	static T& getInstance() {
		assert(spSingleton != nullptr);
		return *spSingleton;
	}

private:
	static T* spSingleton;
	Singleton(Singleton const&) = delete;
	void operator=(Singleton const&) = delete;
};

template<typename T> T* Singleton<T>::spSingleton = 0;