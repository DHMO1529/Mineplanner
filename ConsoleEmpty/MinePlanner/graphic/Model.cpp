#include "MinePlanner/graphic/Model.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <clx/unzip.h>

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/ApplicationConstant.hpp"
namespace MinePlanner{
namespace graphic{
class ModelImpl : public Model
{
public:
	ModelImpl(const char* filename)
	{
		typedef boost::char_separator<char> Separator;
		Separator spaceSeparator(" \r","",boost::drop_empty_tokens);
		Separator spaceSlashSeparator("/ \r","",boost::drop_empty_tokens);
		typedef boost::tokenizer<Separator> Tokenizer;

		clx::unzip unzip(ApplicationConstant::ZIP_ARCHIVE,ApplicationConstant::ZIP_PASSWORD);
		clx::unzip::iterator it = unzip.find(filename);
		clx::unzip::stream_type& stream = *it;

		struct{
			float operator()(const std::string& str){return boost::lexical_cast<float,std::string>(str);}
		}fcast;

		std::vector<glm::vec3> v;
		std::vector<glm::vec2> vt;
		std::vector<glm::vec3> vn;

		std::vector<std::string> buf;
		std::string line;
		while(true)
		{
			std::getline(stream,line);

			if(stream.eof()){break;}

			if(line.length() <= 1)
			{
				continue;
			}

			buf.clear();
			if(line[0] == 'v')
			{
				switch(line[1])
				{
				case ' ':
					{
						Tokenizer tokenizer(line,spaceSeparator);
						BOOST_FOREACH(const std::string& token,tokenizer)
						{
							buf.push_back(token);
						}
						v.push_back(glm::vec3(fcast(buf[1]),fcast(buf[2]),fcast(buf[3])));
					}
					break;
				case 't':
					{
						Tokenizer tokenizer(line,spaceSeparator);
						BOOST_FOREACH(const std::string& token,tokenizer)
						{
							buf.push_back(token);
						}
						vt.push_back(glm::vec2(fcast(buf[1]),fcast(buf[2])));
					}
					break;
				case 'n':
					{
						Tokenizer tokenizer(line,spaceSeparator);
						BOOST_FOREACH(const std::string& token,tokenizer)
						{
							buf.push_back(token);
						}
						vn.push_back(glm::vec3(fcast(buf[1]),fcast(buf[2]),fcast(buf[3])));
					}
					break;
				default:
					break;
				}
			}
			else if(line[0] == 'f')
			{
				struct{
					int operator()(const std::string& str){return boost::lexical_cast<int,std::string>(str);}
				}icast;

				Tokenizer tokenizer(line,spaceSlashSeparator);
				BOOST_FOREACH(const std::string& token,tokenizer)
				{
					buf.push_back(token);
				}

				for(int i = 0 ; i < 3 ; ++i)
				{
					const glm::vec3& addv = v[ icast(buf[1 + i*3]) - 1 ];
					m_vertices.push_back( addv );

					const int vt_index = icast(buf[2 + i*3]);
					if(vt_index != 0)/*色々不十分だが今はこれで十分*/
					{
						const glm::vec2& addt = vt[ vt_index - 1 ];
						m_textureCoords.push_back( addt );
					}

					const glm::vec3& addn = vn[ icast(buf[3 + i*3]) - 1 ];
					m_normals.push_back( addn );
				}
			}
		}
	}
	virtual int numVertex()const
	{
		return m_vertices.size();
	}
	virtual int numTriangle()const
	{
		return m_vertices.size() / 3;
	}

	virtual glm::vec3 getNormal(int index)const
	{
		return m_normals[index];
	}
	virtual glm::vec2 getTextureCoord(int index)const
	{
		return m_textureCoords[index];
	}
	virtual glm::vec3 getVertex(int index)const
	{
		return m_vertices[index];
	}
private:
	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_textureCoords;
	std::vector<glm::vec3> m_normals;
};
Model::ptr Model::createFromArchiveWaveFront(const char* filename)
{
	return Model::ptr(new ModelImpl(filename));
}
}//graphic
}//MinePlanner
