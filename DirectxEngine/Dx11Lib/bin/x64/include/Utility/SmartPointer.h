#ifndef __SPTRCREATOR_H__
#define __SPTRCREATOR_H__

#include <memory>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) if(x) { x->Release(); x = NULL; } 
#endif

template<typename T> 
void ReleasePtr(T *ptr) 
{
	SAFE_RELEASE(ptr);
}


class SmartPointer
{
public:

	template<typename T>
	static inline std::shared_ptr<T> CreateShared(T *ptr)
	{
		return std::shared_ptr<T>(ptr, ReleasePtr<T>);
	}

	template<typename T>
	static inline std::unique_ptr<T> CreateUnique(T *ptr)
	{
		return std::make_unique<T>(ptr);
	}

	template<typename T>
	static inline std::unique_ptr<T> CreateUnique(T ptr)
	{
		return std::make_unique<T>(ptr);
	}

protected:

private:
};


#endif