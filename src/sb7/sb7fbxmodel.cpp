#include "sb7fbxmodel.h"
#include <fbxsdk.h>
#include <vmath.h>
#include <stdlib.h>
#include <shader.h>

namespace sb7
{
	//FbxManager* lSdkManager = FbxManager::Create();
	sb7fbxmodel::sb7fbxmodel(char *fileName)
	{
		FbxManager* lSdkManager = FbxManager::Create();

		// Create the IO settings object.
		FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
		lSdkManager->SetIOSettings(ios);

		// Create an importer using the SDK manager.
		FbxImporter* lImporter = FbxImporter::Create(lSdkManager,"");

		// Use the first argument as the filename for the importer.
		if(!lImporter->Initialize(fileName, -1, lSdkManager->GetIOSettings())) { 
			printf("Call to FbxImporter::Initialize() failed.\n"); 
			printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString()); 
			exit(-1); 
		}

		// Create a new scene so that it can be populated by the imported file.
		FbxScene* lScene = FbxScene::Create(lSdkManager,"myScene");

		// Import the contents of the file into the scene.
		lImporter->Import(lScene);
		ProcessNode(lScene->GetRootNode());

		// The file is imported; so get rid of the importer.
		lImporter->Destroy();
	}

	void sb7fbxmodel::ProcessNode(FbxNode* pNode)
	{
		if(pNode->GetNodeAttribute())
		{
			switch(pNode->GetNodeAttribute()->GetAttributeType())
			{
			case FbxNodeAttribute::eMesh:
				ProcessMesh(pNode);
				break;
			case FbxNodeAttribute::eSkeleton:
				ProcessSkeleton(pNode);
				break;
			case FbxNodeAttribute::eLight:
				ProcessLight(pNode);
				break;
			case FbxNodeAttribute::eCamera:
				ProcessCamera();
				break;
			}
		}

		for(int i = 0 ; i < pNode->GetChildCount() ; ++i)
		{
			ProcessNode(pNode->GetChild(i));
		}
	}

	void sb7fbxmodel::ProcessMesh(FbxNode* pNode)
	{
		fbxsdk::FbxMesh* pMesh = pNode->GetMesh();  
		if(pMesh == NULL)  
		{  
			return;  
		}  

		int triangleCount = pMesh->GetPolygonCount();  
		int vertexCounter = 0;

		sub_mesh sm;
		sm.count = 3 * triangleCount;
		sm.va = (vetex_attr*)malloc(sizeof(vetex_attr) * sm.count);
		m_vass.push_back(sm);


		for(int i = 0 ; i < triangleCount ; ++i)  
		{  
			for(int j = 0 ; j < 3 ; j++)  
			{
				vetex_attr va;
				int ctrlPointIndex = pMesh->GetPolygonVertex(i , j);  

				// Read the vertex  
				ReadVertex(pMesh , ctrlPointIndex , va.vertex);  

				// Read the color of each vertex  
				ReadColor(pMesh , ctrlPointIndex , vertexCounter , va.color);  

				// Read the UV of each vertex  
				for(int k = 0 ; k < 2 ; ++k)
				{  
					ReadUV(pMesh , ctrlPointIndex , pMesh->GetTextureUVIndex(i, j) , k , va.uv[k]);  
				}  

				// Read the normal of each vertex  
				ReadNormal(pMesh , ctrlPointIndex , vertexCounter , va.normal);  

				// Read the tangent of each vertex  
				ReadTangent(pMesh , ctrlPointIndex , vertexCounter , va.tangent);  
				sm.va[vertexCounter] = va;
				vertexCounter++;  
				
			}  

			// 根据读入的信息组装三角形，并以某种方式使用即可，比如存入到列表中、保存到文件等...   
		}
	}

	void sb7fbxmodel::ReadVertex(fbxsdk::FbxMesh* pMesh, int ctrlPointIndex , vmath::vec3& pVertex)  
	{  
		FbxVector4* pCtrlPoint = pMesh->GetControlPoints();  

		pVertex[0] = pCtrlPoint[ctrlPointIndex][0];  
		pVertex[1] = pCtrlPoint[ctrlPointIndex][1];  
		pVertex[2] = pCtrlPoint[ctrlPointIndex][2];  
	} 

	void sb7fbxmodel::ReadColor(fbxsdk::FbxMesh* pMesh, int ctrlPointIndex , int vertexCounter , vmath::vec4& pColor)
	{
		if(pMesh->GetElementVertexColorCount() < 1)
		{
			return;
		}

		fbxsdk::FbxGeometryElementVertexColor* pVertexColor = pMesh->GetElementVertexColor(0);
		switch(pVertexColor->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			{
				switch(pVertexColor->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					{
						pColor[0] = pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mRed;
						pColor[1] = pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mGreen;
						pColor[2] = pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mBlue;
						pColor[3]= pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mAlpha;
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = pVertexColor->GetIndexArray().GetAt(ctrlPointIndex);
						pColor[0] = pVertexColor->GetDirectArray().GetAt(id).mRed;
						pColor[1] = pVertexColor->GetDirectArray().GetAt(id).mGreen;
						pColor[2] = pVertexColor->GetDirectArray().GetAt(id).mBlue;
						pColor[3] = pVertexColor->GetDirectArray().GetAt(id).mAlpha;
					}
					break;

				default:
					break;
				}
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			{
				switch (pVertexColor->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					{
						pColor[0] = pVertexColor->GetDirectArray().GetAt(vertexCounter).mRed;
						pColor[1] = pVertexColor->GetDirectArray().GetAt(vertexCounter).mGreen;
						pColor[2] = pVertexColor->GetDirectArray().GetAt(vertexCounter).mBlue;
						pColor[3] = pVertexColor->GetDirectArray().GetAt(vertexCounter).mAlpha;
					}
					break;
				case FbxGeometryElement::eIndexToDirect:
					{
						int id = pVertexColor->GetIndexArray().GetAt(vertexCounter);
						pColor[0] = pVertexColor->GetDirectArray().GetAt(id).mRed;
						pColor[1] = pVertexColor->GetDirectArray().GetAt(id).mGreen;
						pColor[2] = pVertexColor->GetDirectArray().GetAt(id).mBlue;
						pColor[3]  = pVertexColor->GetDirectArray().GetAt(id).mAlpha;
					}
					break;
				default:
					break;
				}
			}
			break;
		}
	}

	void sb7fbxmodel::ReadUV(fbxsdk::FbxMesh* pMesh, int ctrlPointIndex , int textureUVIndex , int uvLayer , vmath::vec2& pUV)
	{
		if(uvLayer >= 2 || pMesh->GetElementUVCount() <= uvLayer)
		{
			return ;
		}

		fbxsdk::FbxGeometryElementUV* pVertexUV = pMesh->GetElementUV(uvLayer);

		switch(pVertexUV->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			{
				switch(pVertexUV->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					{
						pUV[0] = pVertexUV->GetDirectArray().GetAt(ctrlPointIndex)[0];
						pUV[1] = pVertexUV->GetDirectArray().GetAt(ctrlPointIndex)[1];
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = pVertexUV->GetIndexArray().GetAt(ctrlPointIndex);
						pUV[0] = pVertexUV->GetDirectArray().GetAt(id)[0];
						pUV[1] = pVertexUV->GetDirectArray().GetAt(id)[1];
					}
					break;

				default:
					break;
				}
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			{
				switch (pVertexUV->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				case FbxGeometryElement::eIndexToDirect:
					{
						pUV[0] = pVertexUV->GetDirectArray().GetAt(textureUVIndex)[0];
						pUV[1] = pVertexUV->GetDirectArray().GetAt(textureUVIndex)[1];
					}
					break;

				default:
					break;
				}
			}
			break;
		}
	}

	void sb7fbxmodel::ReadNormal(fbxsdk::FbxMesh* pMesh , int ctrlPointIndex , int vertexCounter , vmath::vec3& pNormal)
	{
		if(pMesh->GetElementNormalCount() < 1)
		{
			return;
		}

		fbxsdk::FbxGeometryElementNormal* leNormal = pMesh->GetElementNormal(0);
		switch(leNormal->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			{
				switch(leNormal->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					{
						pNormal[0] = leNormal->GetDirectArray().GetAt(ctrlPointIndex)[0];
						pNormal[1] = leNormal->GetDirectArray().GetAt(ctrlPointIndex)[1];
						pNormal[2] = leNormal->GetDirectArray().GetAt(ctrlPointIndex)[2];
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = leNormal->GetIndexArray().GetAt(ctrlPointIndex);
						pNormal[0] = leNormal->GetDirectArray().GetAt(id)[0];
						pNormal[1] = leNormal->GetDirectArray().GetAt(id)[1];
						pNormal[2] = leNormal->GetDirectArray().GetAt(id)[2];
					}
					break;

				default:
					break;
				}
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			{
				switch(leNormal->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					{
						pNormal[0] = leNormal->GetDirectArray().GetAt(vertexCounter)[0];
						pNormal[1] = leNormal->GetDirectArray().GetAt(vertexCounter)[1];
						pNormal[2] = leNormal->GetDirectArray().GetAt(vertexCounter)[2];
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = leNormal->GetIndexArray().GetAt(vertexCounter);
						pNormal[0] = leNormal->GetDirectArray().GetAt(id)[0];
						pNormal[1] = leNormal->GetDirectArray().GetAt(id)[1];
						pNormal[2] = leNormal->GetDirectArray().GetAt(id)[2];
					}
					break;

				default:
					break;
				}
			}
			break;
		}
	}
	void sb7fbxmodel::ReadTangent(fbxsdk::FbxMesh* pMesh, int ctrlPointIndex, int vertecCounter, vmath::vec3& pTangent)
	{
		if(pMesh->GetElementTangentCount() < 1)
		{
			return;
		}

		fbxsdk::FbxGeometryElementTangent* leTangent = pMesh->GetElementTangent(0);

		switch(leTangent->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			{
				switch(leTangent->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					{
						pTangent[0] = leTangent->GetDirectArray().GetAt(ctrlPointIndex)[1];
						pTangent[1] = leTangent->GetDirectArray().GetAt(ctrlPointIndex)[2];
						pTangent[2] = leTangent->GetDirectArray().GetAt(ctrlPointIndex)[3];
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = leTangent->GetIndexArray().GetAt(ctrlPointIndex);
						pTangent[0] = leTangent->GetDirectArray().GetAt(id)[0];
						pTangent[1] = leTangent->GetDirectArray().GetAt(id)[1];
						pTangent[2] = leTangent->GetDirectArray().GetAt(id)[2];
					}
					break;

				default:
					break;
				}
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			{
				switch(leTangent->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					{
						pTangent[0] = leTangent->GetDirectArray().GetAt(vertecCounter)[0];
						pTangent[1] = leTangent->GetDirectArray().GetAt(vertecCounter)[1];
						pTangent[2] = leTangent->GetDirectArray().GetAt(vertecCounter)[2];
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = leTangent->GetIndexArray().GetAt(vertecCounter);
						pTangent[0] = leTangent->GetDirectArray().GetAt(id)[0];
						pTangent[1] = leTangent->GetDirectArray().GetAt(id)[1];
						pTangent[2] = leTangent->GetDirectArray().GetAt(id)[2];
					}
					break;

				default:
					break;
				}
			}
			break;
		}
	}

	void sb7fbxmodel::ProcessSkeleton(FbxNode* pNode)
	{}

	void sb7fbxmodel::ProcessLight(FbxNode* pNode)
	{}

	void sb7fbxmodel::ProcessCamera()
	{}

	sb7fbxmodel::~sb7fbxmodel(void)
	{

	}

	void sb7fbxmodel::setup(void)
	{
		GLuint vs;
		GLuint fs;

		vs = sb7::shader::load("media/shaders/draw_triangle/draw_triangle.vs.glsl", GL_VERTEX_SHADER);
		fs = sb7::shader::load("media/shaders/draw_triangle/draw_triangle.fs.glsl", GL_FRAGMENT_SHADER);

		program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glDeleteShader(vs);
		glDeleteShader(fs);
		for (std::vector<sub_mesh>::iterator i = m_vass.begin(); i < m_vass.end(); i++)
			sub_mesh_set_up(*i);
	}

	void sb7fbxmodel::sub_mesh_set_up(sub_mesh& sm)
	{
		glGenVertexArrays(1, &sm.vao);
		glBindVertexArray(sm.vao);
		glGenBuffers(1, &sm.vbo);
		glBindBuffer(GL_ARRAY_BUFFER, sm.vao);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vetex_attr) * sm.count, sm.va, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vetex_attr), NULL);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vetex_attr), (void*)OFFSETOF(vetex_attr, normal));
		glEnableVertexAttribArray(0);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
		//glEnableVertexAttribArray(1);
		glBindVertexArray(0);
	}

	void sb7fbxmodel::render(void)
	{
		glUseProgram(program);
		//glEnable(GL_POLYGON_OFFSET_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, vmath::rotate((float)-90, (float)0, (float)0));
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, vmath::lookat(vmath::vec3(0, 100, 400), vmath::vec3(0, 100, 0), vmath::vec3(0, 1, 0)));
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, vmath::perspective(45, 1, 0.1, 1000));
		glUniform3f(glGetUniformLocation(program, "lightdir"), (float)0, (float)1.0/4.0, (float)1);
		for (std::vector<sub_mesh>::iterator i = m_vass.begin(); i < m_vass.end(); i++)
			sub_mesh_render(*i);
	}

	void sb7fbxmodel::sub_mesh_render(sub_mesh &sm)
	{
		glBindVertexArray(sm.vao);
		glDrawArrays(GL_TRIANGLES, 0, sm.count); 
		glBindVertexArray(0);
	}
}