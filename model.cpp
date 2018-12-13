//
// Created by Alex_Li on 2018/11/27.
//

#include "model.h"

Model::Model(std::istream &is)
{
	getModel(is);
}

void Model::glDrawModel()
{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glTranslated(translate.getX(), translate.getY(), translate.getZ());
//	glRotated(angleX, 1, 0, 0);
//	glRotated(angleY, 0, 1, 0);
//	glRotated(angleZ, 0, 0, 1);

	for(Group &g : group)
	{
		g.glDrawGroup();
	}

//	glLoadIdentity();
}

void Model::getModel(std::istream &is)
{
	std::cout << "Loading model......\n" << std::endl;

	Group *tempGroup = nullptr;
	std::string s;
	while(getline(is, s))
	{
		if(s.empty())
			continue;

		std::stringstream ss(s);
		std::string label;
		ss >> label;

		if(label == "#")
		{
			continue;
		}
		else if(label == "mtllib")
		{
			std::string mtl;
			ss >> mtl;
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
			double x = 0, y = 0, z = 0;
			ss >> x >> y >> z;

//			x /= 100;
//			y /= 100;
//			z /= 100;

			point.emplace_back(x, y, z);
		}
		else if(label == "vt")
		{
			std::vector<double> x(3, 0);
			int i = 0;
			while(ss >> x[i])
			{
				i++;
			}
			texturePoint.emplace_back(x[0], x[1], x[2]);
		}
		else if(label == "vn")
		{
			double x = 0, y = 0, z = 0;
			ss >> x >> y >> z;
			normal.emplace_back(x, y, z);
		}
		else if(label == "usemtl" || label == "g")
		{
			if(tempGroup)
			{
				group.push_back(*tempGroup);
				std::cout << "Group load successfully!\n" << std::endl;
				delete tempGroup;
			}

			tempGroup = new Group();
			std::string groupName;

			if(label == "g")
			{
				ss >> groupName;
				std::cout << groupName << ": Loading group......" << std::endl;
			}
			else
			{
				std::string tID;
				ss >> tID;
				std::cout << tID << ": Loading texture......" << std::endl;
				auto p = texture.find(tID);
				if(p != texture.end())
				{
					tempGroup->setTexture(&p->second);
				}
				else
				{
					std::cout << tID << ": Fail to load texture!" << std::endl;
				}
			}
		}
		else if(label == "s")
		{
			//
		}
		else if(label == "f")
		{
			Surface f;
			std::string coordinate;
			while(ss >> coordinate)
			{
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
		group.push_back(*tempGroup);
		std::cout << "Group load successfully!\n" << std::endl;
		delete tempGroup;
	}

	std::cout << "Model successfully loaded!" << std::endl;
}

void Model::loadMTL(std::istream &is)
{
	std::string s;
	std::string temp;
//	Material material;
	Texture material;
	std::string tID;
	bool first = true;
	std::string op;
	while(getline(is, s))
	{
		std::stringstream ss(s);
		ss >> op;
		if(op == "newmtl")
		{
			if(!first)
			{
				texture[temp] = material;
				tID = "";
			}
			else
			{
				first = false;
			}
			ss >> temp;
		}
//		if (op=="Ns")
//			ss>>material.ns;
//		if (op=="Ka")
//			ss>>material.ka[0]>>material.ka[1]>>material.ka[2];
//		if (op=="Kd")
//			ss>>material.kd[0]>>material.kd[1]>>material.kd[2];
//		if (op=="Ks")
//			ss>>material.ks[0]>>material.ks[1]>>material.ks[2];
//		if (op=="Ke")
//			ss>>material.ke[0]>>material.ke[1]>>material.ke[2];
//		if (op=="Ni")
//			ss>>material.ni;
		if(op == "map_Kd" || op == "map_Bump")
		{
			std::string tempTexture;
			ss >> tempTexture;
			for(char &i : tempTexture)
				if(i == '\\')
					i = ' ';    //adjust to relative path
			std::stringstream tt(tempTexture);
			while(tt >> tID);
			material.setTexture(tID);
		}
	}
}

void Model::decode(std::string s, Surface &surface)
{
	std::string pattern1 = "[1-9][0-9]*";
	std::string pattern2 = "[1-9][0-9]*/[1-9][0-9]*";
	std::string pattern3 = "[1-9][0-9]*//[1-9][0-9]*";
	std::string pattern4 = "[1-9][0-9]*/[1-9][0-9]*/[1-9][0-9]*";
	std::regex regex1(pattern1);
	std::regex regex2(pattern2);
	std::regex regex3(pattern3);
	std::regex regex4(pattern4);

	int mode = 0;
	if(std::regex_match(s, regex4))
	{
		mode = 4;
	}
	else if(std::regex_match(s, regex3))
	{
		mode = 3;
	}
	else if(std::regex_match(s, regex2))
	{
		mode = 2;
	}
	else if(std::regex_match(s, regex1))
	{
		mode = 1;
	}
//	std::cout << mode << std::endl;

	for(char &c : s)
	{
		if(c == '/')
			c = ' ';
	}

	std::stringstream ss(s);
	unsigned int i = 0;
	std::vector<unsigned int> x;
	while(ss >> i)
	{
		x.push_back(i);
	}

	if(mode == 1)
	{
		surface.addPoint(point[x[0]]);
	}
	else if(mode == 2)
	{
		surface.addPoint(point[x[0]]);
		surface.addTexturePoint(texturePoint[x[1]]);
		surface.setHasTexture(true);
	}
	else if(mode == 3)
	{
		surface.addPoint(point[x[0]]);
		surface.setNormal(normal[x[1]]);
	}
	else if(mode == 4)
	{
		surface.addPoint(point[x[0]]);
		surface.addTexturePoint(texturePoint[x[1]]);
		surface.setNormal(normal[x[2]]);
		surface.setHasTexture(true);
	}
}

void Model::translateModel(double x, double y, double z)
{
	for(Group &g : group)
	{
		g.translateGroup(x, y, z);
	}
}

void Model::rotateModel(double angleX, double angleY, double angleZ)
{
	Model::angleX = angleX;
	Model::angleY = angleY;
	Model::angleZ = angleZ;
}

//std::string Model::getGroup(std::istream &is, Group &g)
//{
//	std::string line;
//	while(getline(is, line))
//	{
//		std::stringstream ss(line);
//		std::string label;
//		ss >> label;
//
//		if(label == "usemtl" && !g.haveTexture())
//		{
//			std::string tID;
//			ss >> tID;
//			auto p = texture.find(tID);
//			if(p != texture.end())
//			{
//				g.setTexture(&p->second);
//			}
//			else
//			{
//				std::cout << "Can't load texture " << tID << "!" << std::endl;
//			}
//		}
//		else if(label == "usemtl" && g.haveTexture())
//		{
//			return line;
//		}
//		else if(label == "f")
//		{
//			Surface f;
//			std::string coordinate;
//			while(ss >> coordinate)
//			{
//				decode(coordinate, f);
//			}
//			g.addSurface(f);
//		}
//		else if(label == "s")
//		{
//			//
//		}
//		else if(label == "o")
//		{
//			return line;
//		}
//		else
//		{
//			//
//		}
//	}
//}
