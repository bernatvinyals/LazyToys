#include "File.h"

File::File()
{
	isBinary = false;
	size = 0;
	buffer = nullptr;
	failedToOpen = false;
}

File::File(const char* _dir, std::ios_base::openmode _action)
{
	isBinary = false;
	size = 0;
	buffer = nullptr;
	failedToOpen = false;
	char a = _action & std::ios::binary;
	char b = std::ios::binary;
	if (a == b)
	{
		isBinary = true;
	}
	stream.open(_dir, _action);
	if (!stream.is_open()) 
	{ 
		printf("Can't open file");
		failedToOpen = true;
		stream.close();

		return; 
	}
}

File::~File()
{
}

char* File::GetBinaryBuffer()
{
	return buffer;
}

std::string* File::GetTextBuffer()
{
	return &textBuffer;
}

int File::Read()
{
	if (!failedToOpen)
	{
		if (isBinary)
		{
			if (stream.is_open()) {
				stream.seekg(0, stream.end);
				size = stream.tellg();
				stream.seekg(0, stream.beg);
				buffer = new char[size];
				stream.read(buffer, size);
				return 1;
			}
			return 0;
		}
		else
		{
			if (stream.is_open()) {
				bool first = false;
				while (!stream.eof())
				{
					std::string aux = std::string();
					std::getline(stream, aux);
					if (!first)
					{
						textBuffer.append(aux);
						first = true;
					}
					else
					{
						textBuffer.append("\n").append(aux);
					}
				}
				size = textBuffer.size();
				return 1;
			}
			return 0;
		}
	}
	stream.close();

	return 0;
}

int File::Write(const char* _dir, bool _binary, int _size)
{
	if (_dir=="")
	{
		if (isBinary)
		{
			if (_size <= 0)
			{
				_size = sizeof(buffer);
			}
			stream.write(buffer, _size);
		}
		else
		{
			int tempSize = 0;
			if (_size <= 0)
			{
				tempSize = size;
			}
			stream.write(textBuffer.c_str(), tempSize);

		}
	}
	else
	{
		if (_binary)
		{
			std::ofstream outfile(_dir, std::ofstream::binary);
			if (_size <= 0)
			{
				_size = sizeof(buffer);
			}
			outfile.write(buffer, _size);
			outfile.close();
		}
		else
		{
			std::ofstream outfile(_dir, std::ofstream::out);
			int tempSize = 0;
			if (_size <=0)
			{
				tempSize = size;
			}
			outfile.write(textBuffer.c_str(), tempSize);
			outfile.close();
		}
	}
	return 0;
}

int File::Write(char* _buffer, int _size, bool _binary, const char* _dir)
{
	if (_dir == "")
	{
		if (isBinary)
		{
			stream.write(_buffer, _size);
		}
		else
		{
			stream.write(_buffer, _size);
		}
	}
	else
	{
		if (_binary)
		{
			std::ofstream outfile(_dir, std::ofstream::binary);
			outfile.write(_buffer, _size);
			outfile.close();
		}
		else
		{
			std::ofstream outfile(_dir, std::ofstream::out);
			outfile.write(_buffer, _size);
			outfile.close();
		}
	}
	return 0;
}

void File::Flush()
{
	delete[] buffer;
}
