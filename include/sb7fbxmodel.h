#pragma once
#include <fbxsdk.h>
#include <sb7.h>
#include <vmath.h>
#include <vector>


#define OFFSETOF(type, field)    ((unsigned long) &(((type *) 0)->field))
namespace sb7
{
typedef struct _vetex_attr
{
	vmath::vec3 vertex;
	vmath::vec3 normal;
	vmath::vec4 color;
	vmath::vec3 tangent;
	vmath::vec2 uv[2];
}vetex_attr;

typedef struct _sub_mesh
{
	vetex_attr* va;
	unsigned count;
	GLuint vao;
	GLuint vbo;
}sub_mesh;
class sb7fbxmodel
{
public:
	sb7fbxmodel(char* fileName);
	void ProcessNode(FbxNode* pNode);
	void ProcessMesh(FbxNode* pNode);
	void ProcessSkeleton(FbxNode* pNode);
	void ProcessLight(FbxNode* pNode);
	void ProcessCamera();
	void sb7fbxmodel::ReadVertex(FbxMesh* pMesh, int ctrlPointIndex , vmath::vec3& pVertex);
	void ReadColor(FbxMesh* pMesh , int ctrlPointIndex , int vertexCounter , vmath::vec4& pColor);
	void ReadUV(FbxMesh* pMesh , int ctrlPointIndex , int textureUVIndex , int uvLayer , vmath::vec2& pUV);
	void ReadNormal(FbxMesh* pMesh , int ctrlPointIndex , int vertexCounter , vmath::vec3& pNormal);
	void ReadTangent(FbxMesh* pMesh , int ctrlPointIndex , int vertecCounter , vmath::vec3& pTangent);
	void setup(void);
	void render(void);
	void sub_mesh_set_up(sub_mesh& sm);
	void sub_mesh_render(sub_mesh &sm);
	~sb7fbxmodel(void);

private:
	std::vector<sub_mesh> m_vass;
	GLuint program;
};
}
