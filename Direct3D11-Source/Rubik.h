#ifndef RUBIK_H
#define RUBIK_H

#include <wrl/client.h>
#include "Effects.h"

enum RubikFaceColor {
	RubikFaceColor_Black,		// ��ɫ
	RubikFaceColor_Orange,		// ��ɫ
	RubikFaceColor_Red,			// ��ɫ
	RubikFaceColor_Green,		// ��ɫ
	RubikFaceColor_Blue,		// ��ɫ
	RubikFaceColor_Yellow,		// ��ɫ
	RubikFaceColor_White		// ��ɫ
};

enum RubikFace {
	RubikFace_PosX,		// +X��
	RubikFace_NegX,		// -X��
	RubikFace_PosY,		// +Y��
	RubikFace_NegY,		// -Y��
	RubikFace_PosZ,		// +Z��
	RubikFace_NegZ,		// -Z��
};

struct Cube
{
	// ��ȡ��ǰ��������������
	DirectX::XMMATRIX GetWorldMatrix() const;

	RubikFaceColor faceColors[6];	// ���������ɫ������0-5�ֱ��Ӧ+X, -X, +Y, -Y, +Z, -Z��
	DirectX::XMFLOAT3 pos;			// ��ת��������������λ��
	DirectX::XMFLOAT3 rotation;		// ���������ڵ�����ת����¼��ǰ�ֱ���x��, y��, z����ת�Ļ���

};


class Rubik
{
public:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	// ��ʼ����Դ
	void InitResources(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	// ������ԭħ��
	void Reset();
	// ����ħ��״̬
	void Update();
	// ����ħ��
	void Draw(ComPtr<ID3D11DeviceContext> deviceContext, BasicEffect& effect);
	// ��ȡ��������
	ComPtr<ID3D11ShaderResourceView> GetTexArray() const;
private:
	// ħ�� [X][Y][Z]
	Cube mCubes[3][3][3];

	// ���㻺����������6�����24������
	// ����0-3��Ӧ+X��
	// ����4-7��Ӧ-X��
	// ����8-11��Ӧ+Y��
	// ����12-15��Ӧ-Y��
	// ����16-19��Ӧ+Z��
	// ����20-23��Ӧ-Z��
	ComPtr<ID3D11Buffer> mVertexBuffer;	

	// ��������������6������
	ComPtr<ID3D11Buffer> mIndexBuffer;
	
	// �������飬����7������
	ComPtr<ID3D11ShaderResourceView> mTexArray;
};




#endif