#include "TextureMappingShader.h"
#include "Render/Texture.h"

namespace Blue
{
	TextureMappingShader::TextureMappingShader()
		: Shader(L"TextureMapping")
	{
	}

	TextureMappingShader::TextureMappingShader(const std::string& textureName)
		: Shader(L"TextureMapping")
	{
		// 텍스처 생성.
		texture = std::make_unique<Texture>(textureName);
	}

	void TextureMappingShader::Bind()
	{
		Shader::Bind();

		if (texture)
		{
			texture->Bind();
		}
	}
}