#ifndef RUBIK_H
#define RUBIK_H

#include <wrl/client.h>
#include "Effects.h"

enum RubikFaceColor {
	RubikFaceColor_Black,		// 黑色
	RubikFaceColor_Orange,		// 橙色
	RubikFaceColor_Red,			// 红色
	RubikFaceColor_Green,		// 绿色
	RubikFaceColor_Blue,		// 蓝色
	RubikFaceColor_Yellow,		// 黄色
	RubikFaceColor_White		// 白色
};

enum RubikFace {
	RubikFace_PosX,		// +X面
	RubikFace_NegX,		// -X面
	RubikFace_PosY,		// +Y面
	RubikFace_NegY,		// -Y面
	RubikFace_PosZ,		// +Z面
	RubikFace_NegZ,		// -Z面
};

struct Cube
{
	// 获取当前立方体的世界矩阵
	DirectX::XMMATRIX GetWorldMatrix() const;

	RubikFaceColor faceColors[6];	// 六个面的颜色，索引0-5分别对应+X, -X, +Y, -Y, +Z, -Z面
	DirectX::XMFLOAT3 pos;			// 旋转结束后中心所处位置
	DirectX::XMFLOAT3 rotation;		// 仅允许存在单轴旋转，记录当前分别绕x轴, y轴, z轴旋转的弧度

};


class Rubik
{
public:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	// 初始化资源
	void InitResources(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	// 立即复原魔方
	void Reset();
	// 更新魔方状态
	void Update();
	// 绘制魔方
	void Draw(ComPtr<ID3D11DeviceContext> deviceContext, BasicEffect& effect);
	// 获取纹理数组
	ComPtr<ID3D11ShaderResourceView> GetTexArray() const;
private:
	// 魔方 [X][Y][Z]
	Cube mCubes[3][3][3];

	// 顶点缓冲区，包含6个面的24个顶点
	// 索引0-3对应+X面
	// 索引4-7对应-X面
	// 索引8-11对应+Y面
	// 索引12-15对应-Y面
	// 索引16-19对应+Z面
	// 索引20-23对应-Z面
	ComPtr<ID3D11Buffer> mVertexBuffer;	

	// 索引缓冲区，仅6个索引
	ComPtr<ID3D11Buffer> mIndexBuffer;
	
	// 纹理数组，包含7张纹理
	ComPtr<ID3D11ShaderResourceView> mTexArray;
};




#endif