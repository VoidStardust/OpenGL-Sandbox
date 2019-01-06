//
// Created by Alex_Li on 2018/11/27.
//

#include "model.h"

Model::Model(double ratio) : ratio(ratio) {}

Model::Model(std::istream &is)
{
	getModel(is);
}

void Model::glDrawModel()
{
	for(Group &g : group)
	{
		g.glDrawGroup();
	}
}

void Model::getModel(std::istream &is)
{
	std::cout << "Loading model......\n" << std::endl;

	Group *tempGroup = nullptr;
	std::string s;
	double maxX = -1e10;
	double maxY = -1e10;
	double maxZ = -1e10;
	double minX = 1e10;
	double minY = 1e10;
	double minZ = 1e10;

	while(getline(is, s))
	{
		if(s.empty())
			continue;

		std::vector<std::string> List = std::move(stringToken(s));
		std::string label = List[0];

		if(label[0] == '#')
		{
			continue;
		}
		else if(label == "mtllib")
		{
			std::string mtl = List[1];
			std::ifstream file(mtl);
			if(file)
			{
				std::cout << "Loading file " << mtl << "......" << std::endl;
				loadMTL(file);
				file.close();
				std::cout << std::endl;
			}
			else
			{
				std::cout << mtl << ": File does not exist.\n" << std::endl;
			}
		}
		else if(label == "o")
		{
			//
		}
		else if(label == "v")
		{
			double x = std::stod(List[1]);
			double y = std::stod(List[2]);
			double z = std::stod(List[3]);

			x *= ratio;
			y *= ratio;
			z *= ratio;

			maxX = std::max(maxX, x);
			maxY = std::max(maxY, y);
			maxZ = std::max(maxZ, z);
			minX = std::min(minX, x);
			minY = std::min(minY, y);
			minZ = std::min(minZ, z);

			point.emplace_back(x, y, z);
		}
		else if(label == "vt")
		{
			std::vector<double> x;
			for(int i = 1; i < List.size(); ++i)
			{
				x.emplace_back(std::stod(List[i]));
			}
			texturePoint.emplace_back(x[0], x[1], x[2]);
		}
		else if(label == "vn")
		{
			double x = std::stod(List[1]);
			double y = std::stod(List[2]);
			double z = std::stod(List[3]);
			normal.emplace_back(x, y, z);
		}
//		else if(label == "usemtl" || label == "g")
		else if(label == "usemtl")
		{
			if(tempGroup)
			{
				group.push_back(std::move(*tempGroup));
				std::cout << "Group load successfully!\n" << std::endl;
				delete tempGroup;
			}

			tempGroup = new Group();
			std::string groupName;

			if(label == "g")
			{
				groupName = List[1];
				std::cout << groupName << ": Loading group......" << std::endl;
			}
			else
			{
				std::string mtlID = List[1];
				std::cout << mtlID << ": Loading material......" << std::endl;
				auto p = material.find(mtlID);
				if(p != material.end())
				{
					tempGroup->setTexture(p->second.getTexture());
				}
				else
				{
					std::cout << mtlID << ": Fail to load material!" << std::endl;
				}
			}
		}
		else if(label == "g")
		{
			//
		}
		else if(label == "s")
		{
			//
		}
		else if(label == "f")
		{
			Surface f;
			std::string coordinate;
			for(int i = 1; i < List.size(); ++i)
			{
				coordinate = List[i];
				decode(coordinate, f);
			}
			tempGroup->addSurface(f);
		}
		else
		{
			std::cout << "Unknown label " << label << std::endl;
		}
	}

	if(tempGroup)
	{
		group.push_back(std::move(*tempGroup));
		std::cout << "Group load successfully!\n" << std::endl;
		delete tempGroup;
	}

	center.setPoint((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2);
	std::cout<< center.getX()<<' '<<center.getY()<<' '<<center.getZ()<<std::endl;
	std::cout << "Model successfully loaded!" << std::endl;
}

void Model::loadMTL(std::istream &is)
{
	Material *tempMaterial = nullptr;
	std::string materialName;
	std::string s;

	while(getline(is, s))
	{
		if(s.empty())
			continue;

		std::vector<std::string> List = stringToken(s);
		std::string label = List[0];

		if(label[0] == '#')
		{
			continue;
		}
		else if(label == "newmtl")
		{
			if(tempMaterial)
			{
				material[materialName] = std::move(*tempMaterial);
				delete tempMaterial;
				materialName.clear();
			}

			tempMaterial = new Material();
			materialName = List[1];

			std::cout << materialName << ": Loading new material......" << std::endl;
		}
		else if(label == "Ns")
		{
			tempMaterial->setNs(std::stod(List[1]));
		}
		else if(label == "Ka")
		{
			std::vector<double> ka;
			for(int i = 1; i < List.size(); ++i)
			{
				ka.emplace_back(std::stod(List[i]));
			}
			tempMaterial->setKa(ka);
		}
		else if(label == "Kd")
		{
			std::vector<double> kd;
			for(int i = 1; i < List.size(); ++i)
			{
				kd.emplace_back(std::stod(List[i]));
			}
			tempMaterial->setKd(kd);
		}
		else if(label == "Ks")
		{
			std::vector<double> ks;
			for(int i = 1; i < List.size(); ++i)
			{
				ks.emplace_back(std::stod(List[i]));
			}
			tempMaterial->setKs(ks);
		}
		else if(label == "Ke")
		{
			std::vector<double> ke;
			for(int i = 1; i < List.size(); ++i)
			{
				ke.emplace_back(std::stod(List[i]));
			}
			tempMaterial->setKe(ke);
		}
		else if(label == "Ni")
		{
			tempMaterial->setNi(std::stod(List[1]));
		}
		else if(label == "map_Kd" || label == "map_Bump" || label == "refl")
		{
			std::string file = List[1];
			for(int i = 2; i < List.size(); ++i)
			{
				file += " " + List[i];
			}
			tempMaterial->setTexture(file);
		}
		else if(label == "d")
		{
			tempMaterial->setD(std::stod(List[1]));
		}
		else if(label == "illum")
		{
			//
		}
		else
		{
			std::cout << "Unknown label " << label << std::endl;
		}
	}

	if(tempMaterial)
	{
		material[materialName] = std::move(*tempMaterial);
		delete tempMaterial;
		materialName.clear();
	}
}

void Model::decode(std::string s, Surface &surface)
{
	int mode = 1;
	unsigned long long int begin = s.find('/');

	if(begin != std::string::npos)
	{
		unsigned long long int n = s.rfind('/') - begin;
		if(n == 0)
			mode = 2;
		else if(n == 1)
			mode = 3;
		else
			mode = 4;
	}

	std::vector<std::string> List = std::move(stringToken(s, '/'));

	if(mode == 1)
	{
		surface.addPoint(point[std::stoi(List[0])]);
	}
	else if(mode == 2)
	{
		surface.addPoint(point[std::stoi(List[0])]);
		surface.addTexturePoint(texturePoint[std::stoi(List[1])]);
	}
	else if(mode == 3)
	{
		surface.addPoint(point[std::stoi(List[0])]);
		surface.setNormal(normal[std::stoi(List[1])]);
	}
//	else if(mode == 4)
	else
	{
		surface.addPoint(point[std::stoi(List[0])]);
		surface.addTexturePoint(texturePoint[std::stoi(List[1])]);
		surface.setNormal(normal[std::stoi(List[2])]);
	}
}

void Model::translateModel(double x, double y, double z)
{
	for(Group &g : group)
	{
		g.translateGroup(x, y, z);
	}
	center.movePoint(x, y, z);
}

void Model::rotateModel(Point center, Vector axis, double angle)
{
	for(Group &g : group)
	{
		g.rotateGroup(center, axis, angle);
	}
	Model::center.rotatePoint(center, axis, angle);
}

void Model::rotateModel(Vector axis, double angle)
{
	for(Group &g : group)
	{
		g.rotateGroup(center, axis, angle);
	}
}

std::vector<std::string> Model::stringToken(std::string token, char match)
{
	token += match;
	std::vector<std::string> ret;
	for(auto p = token.begin(); p != token.end(); p++)
	{
		if(*p == match)
		{
			continue;
		}

		auto q = p + 1;
		while(true)
		{
			if(*q == match)
			{
				std::string s(p, q);
				ret.push_back(s);
				p = q;
				break;
			}
			q++;
		}
	}
	return ret;
}

bool Model::movePath(std::vector<Vector> path)
{
	static unsigned int pos = 0;
	Vector p = path[pos];
	translateModel(p.getX(), p.getY(), p.getZ());
	if(pos + 1 == path.size())
	{
		pos = 0;
		return true;
	}
	else
	{
		pos++;
		return false;
	}
}

void Model::setCenter(const Point &point)
{
	Model::center = point;
}

Point Model::getCenter() const
{
	return center;
}
