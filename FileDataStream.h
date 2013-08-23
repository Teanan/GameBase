#ifndef FILEDATASTREAM_H_INCLUDED
#define FILEDATASTREAM_H_INCLUDED

#include "DataStream.h"

#include <string>
#include <fstream>

class FileDataStream: public DataStream
{
	public:
		
		enum OpenMode
		{
			Read = 1,
			Write
		};

		FileDataStream(std::string fileName, OpenMode mode)
			: m_fileName(fileName), m_mode(mode)
		{
			if (m_mode == Read) m_fileRead = new std::ifstream;
			if (m_mode == Write) m_fileWrite = new std::ofstream;

			open();
		};
        
        ~FileDataStream(){
			close();
        };
        
        void open(){
			if (m_mode == Read) m_fileRead->open(m_fileName.c_str(), std::ios::binary);
			if (m_mode == Write) m_fileWrite->open(m_fileName.c_str(), std::ios::out | std::ios::binary);

			if (m_mode == Read){
				std::string data;
				while(m_fileRead->good()){
					char c;
					m_fileRead->get(c);
					data += c;
				}
				append((void*)data.c_str(), data.size());
			}
        };
        
        void close(){
			if (m_mode == Write){
				std::string data((char*)getData(), getDataSize());
				m_fileWrite->write(data.c_str(), data.size());
			}

			if (m_mode == Read) m_fileRead->close();
			if (m_mode == Write) m_fileWrite->close();
        };

		bool good(){
			if (m_mode == Read) return m_fileRead->good();
			if (m_mode == Write) return m_fileWrite->good();

			return false;
		};

	protected:

		std::string m_fileName;
		OpenMode m_mode;

        std::ifstream* m_fileRead;
        std::ofstream* m_fileWrite;
};

#endif // FILEDATASTREAM_H_INCLUDED