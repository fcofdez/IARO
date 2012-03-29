#include "xmlExporter.hpp"
 
using namespace std;

vector<Triangle *>
readXMLMesh(string path)
{
  // Load the xml file, I put your XML in a file named test.xml
  
  TiXmlDocument XMLdoc(path);
  bool loadOkay = XMLdoc.LoadFile();
  vector<Triangle *> mesh;
  vector<Vector> triangle;
  triangle.resize(3);
  int vectors = 0;

  if (loadOkay)
    {
      cout << path <<" loaded" << endl;
      TiXmlElement *pRoot, *pMesh,  *pPoint, *pNormal, *pTriangle;
      pRoot = XMLdoc.FirstChildElement( "Scene" );
      if ( pRoot )
        {
          // Parse parameters
          pMesh = pRoot->FirstChildElement("Mesh");
          while ( pMesh )
            {
              //cout << "Mesh: name= " << pMesh->Attribute("name") << endl;
              pTriangle = pMesh->FirstChildElement("Triangle");
              while (pTriangle)
                {
                  pPoint = pTriangle->FirstChildElement("point");
                  while (pPoint)
                    {                    
                      double x , y , z;
                      istringstream i(pPoint->GetText());
                      i >> x >> y >> z;
                      triangle.at(vectors) = Vector(x,y,z);
                      pPoint = pPoint->NextSiblingElement("point");
                      vectors++;
                      if (vectors == 3) vectors = 0;
                    }                            
                  pNormal = pTriangle->FirstChildElement("vectorNormal");
                  double xn, yn, zn;
                  istringstream in(pNormal->GetText());
                  in >> xn >> yn >> zn;                 
                  mesh.push_back(new Triangle(triangle.at(0), triangle.at(1), triangle.at(2), Vector(xn,yn,zn), pMesh->Attribute("name")));
                  pTriangle = pTriangle->NextSiblingElement("Triangle");
                }
              pMesh = pMesh->NextSiblingElement( "Mesh" );
            }
         }
      else
        {
          cerr << "Cannot find 'Scene' node" << endl;
        }
 
    }
  else
    cerr << "Can't read file" << endl;
  return mesh;
}


vector<LightSource *>
readXMLLight(string path)
{
  // Load the xml file, I put your XML in a file named test.xml
  
  TiXmlDocument XMLdoc(path);
  bool loadOkay = XMLdoc.LoadFile();
  vector<LightSource *> lights;
  

  if (loadOkay)
    {
      cout << path <<" loaded" << endl;
      TiXmlElement *pRoot, *pRotation,  *pLocation, *pEnergy, *pLight;
      pRoot = XMLdoc.FirstChildElement( "Scene" );
      if ( pRoot )
        {
          // Parse parameters
          pLight = pRoot->FirstChildElement("Light");
          while ( pLight )
            {
              //cout << "Mesh: name= " << pMesh->Attribute("name") << endl;
              pLocation = pLight->FirstChildElement("Location");
              double x , y , z, rx, ry, rz, energy;
              istringstream i(pLocation->GetText());
              i >> x >> y >> z;
              pRotation = pLight->FirstChildElement("Rotation");
              istringstream j(pRotation->GetText());
              j >> rx >> ry >> rz;
              pEnergy = pLight->FirstChildElement("Energy");
              istringstream k(pEnergy->GetText());
              k >> energy;
              lights.push_back(new LightSource(string(pLight->Attribute("name")),
                                               Vector(x,y,z),
                                               Vector(rx,ry,rz),
                                               energy));
              pLight = pLight->NextSiblingElement( "Light" );
            }
        }
      else
        {
          cerr << "Cannot find 'Scene' node" << endl;
        }
 
    }
  else
    cerr << "Can't read file" << endl;
  return lights;
}


void
createXMLLightImpacts(std::map<std::string,int> hits)
{
  TiXmlDocument doc;
  std::map<std::string,int>::iterator it;

  TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
  TiXmlElement * element;
  TiXmlElement * root = new TiXmlElement("Scene");
  TiXmlText * text;
  std::stringstream ss;
  doc.LinkEndChild( decl );
  doc.LinkEndChild( root );
  
  for (it = hits.begin(); it != hits.end(); it++)
    {
      element = new TiXmlElement( "Mesh" );
      element->SetAttribute("name",(*it).first);
      ss << (*it).second;
      text = new TiXmlText( ss.str() );
      element->LinkEndChild( text );
      root->LinkEndChild( element );
    }
  
  doc.SaveFile( "/tmp/lightsImpacts.xml" );

}

