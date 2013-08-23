#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

template <typename T>
class Singleton
{
	protected:

		Singleton()
		{
			m_instance = 0;
		};

		~Singleton(){
			
		};

	public:

		static T* instance(){
			if (m_instance == 0) m_instance = new T;

			return m_instance;
		};

	private:

		static T* m_instance;
};

template <typename T>
T* Singleton<T>::m_instance;

#endif // SINGLETON_H_INCLUDED