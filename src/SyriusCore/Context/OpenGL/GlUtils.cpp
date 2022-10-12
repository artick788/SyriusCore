#include "GlUtils.hpp"

namespace Syrius{

    GLenum getGlShaderType(SR_SHADER_TYPE type){
        switch (type){
            case SR_SHADER_VERTEX:      return GL_VERTEX_SHADER;
            case SR_SHADER_FRAGMENT:    return GL_FRAGMENT_SHADER;
            case SR_SHADER_GEOMETRY:    return GL_GEOMETRY_SHADER;
            case SR_SHADER_TESSELATION: return GL_TESS_EVALUATION_SHADER;
            case SR_SHADER_COMPUTE:     return GL_COMPUTE_SHADER;
            default: {
                SR_CORE_WARNING("Invalid type given to converter, return default: GL_VERTEX_SHADER");
                return GL_VERTEX_SHADER;
            }
        }
    }

    GLenum getGlDrawType(SR_DRAW_TYPE type){
        switch(type){
            case SR_DRAW_POINTS:            return GL_POINTS;
            case SR_DRAW_LINES:             return GL_LINES;
            case SR_DRAW_LINES_STRIP:       return GL_LINE_STRIP;
            case SR_DRAW_TRIANGLES:         return GL_TRIANGLES;
            case SR_DRAW_TRIANGLE_STRIP:    return GL_TRIANGLE_STRIP;
            default: {
                SR_CORE_WARNING("Invalid type given to converter, return default: GL_TRIANGLES");
                return GL_TRIANGLES;
            }
        }
    }

    GLenum getGlDataType(SR_DATA_TYPE type){
        switch (type) {
            case SR_INT8:       return GL_BYTE;
            case SR_UINT8:      return GL_UNSIGNED_BYTE;
            case SR_INT16:      return GL_SHORT;
            case SR_UINT16:     return GL_UNSIGNED_SHORT;
            case SR_INT32:      return GL_INT;
            case SR_UINT32:     return GL_UNSIGNED_INT;
            case SR_INT64:      return GL_INT64_ARB;
            case SR_UINT64:     return GL_UNSIGNED_INT64_ARB;
            case SR_FLOAT16:    return GL_HALF_FLOAT;
            case SR_FLOAT32:    return GL_FLOAT;
            case SR_FLOAT64:    return GL_DOUBLE;
            default: {
                SR_CORE_WARNING("Invalid type given to converter, return default: GL_FLOAT");
                return GL_FLOAT;
            }
        }
    }

    GLenum getGlBufferType(SR_BUFFER_TYPE type){
        switch (type){
            case SR_BUFFER_DEFAULT: return GL_STATIC_DRAW;
            case SR_BUFFER_DYNAMIC: return GL_DYNAMIC_DRAW;
            case SR_BUFFER_STATIC:  return GL_STATIC_DRAW;
            default: {
                SR_CORE_WARNING("Invalid type given to converter, return default: GL_STATIC_DRAW");
                return GL_STATIC_DRAW;
            }
        }
    }

    GLenum getGlTextureType(SR_TEXTURE_FORMAT type){
        switch (type) {
            case SR_TEXTURE_FORMAT_R:       return GL_RED;
            case SR_TEXTURE_FORMAT_RG:      return GL_RG;
            case SR_TEXTURE_FORMAT_RGB:     return GL_RGB;
            case SR_TEXTURE_FORMAT_RGBA:    return GL_RGBA;
            case SR_TEXTURE_FORMAT_BGR:     return GL_BGR;
            case SR_TEXTURE_FORMAT_BGRA:    return GL_BGRA;
            default: {
                SR_CORE_WARNING("Invalid type given to converter, return default: GL_RGBA");
                return GL_RGBA;
            }
        }
    }

    GLint getGlTextureInternalFormat(SR_TEXTURE_DATA_FORMAT format){
        switch (format) {
            case SR_TEXTURE_DATA_FORMAT_R8:         return GL_R8;
            case SR_TEXTURE_DATA_FORMAT_R_I8:       return GL_R8I;
            case SR_TEXTURE_DATA_FORMAT_R_I16:      return GL_R16I;
            case SR_TEXTURE_DATA_FORMAT_R_I32:      return GL_R32I;
            case SR_TEXTURE_DATA_FORMAT_R_UI8:      return GL_R8UI;
            case SR_TEXTURE_DATA_FORMAT_R_UI16:     return GL_R16UI;
            case SR_TEXTURE_DATA_FORMAT_R_UI32:     return GL_R32UI;
            case SR_TEXTURE_DATA_FORMAT_R_F16:      return GL_R16F;
            case SR_TEXTURE_DATA_FORMAT_R_F32:      return GL_R32F;
            case SR_TEXTURE_DATA_FORMAT_RG_8:       return GL_RG8;
            case SR_TEXTURE_DATA_FORMAT_RG_I8:      return GL_RG8I;
            case SR_TEXTURE_DATA_FORMAT_RG_I16:     return GL_RG16I;
            case SR_TEXTURE_DATA_FORMAT_RG_I32:     return GL_RG32I;
            case SR_TEXTURE_DATA_FORMAT_RG_UI8:     return GL_RG8UI;
            case SR_TEXTURE_DATA_FORMAT_RG_UI16:    return GL_RG16UI;
            case SR_TEXTURE_DATA_FORMAT_RG_UI32:    return GL_RG32UI;
            case SR_TEXTURE_DATA_FORMAT_RG_F16:     return GL_RG16F;
            case SR_TEXTURE_DATA_FORMAT_RG_F32:     return GL_RG32F;
            case SR_TEXTURE_DATA_FORMAT_RGB_8:      return GL_RGB8;
            case SR_TEXTURE_DATA_FORMAT_RGB_I8:     return GL_RGB8I;
            case SR_TEXTURE_DATA_FORMAT_RGB_I16:    return GL_RGB16I;
            case SR_TEXTURE_DATA_FORMAT_RGB_I32:    return GL_RGB32I;
            case SR_TEXTURE_DATA_FORMAT_RGB_UI8:    return GL_RGB8UI;
            case SR_TEXTURE_DATA_FORMAT_RGB_UI16:   return GL_RGB16UI;
            case SR_TEXTURE_DATA_FORMAT_RGB_UI32:   return GL_RGB32UI;
            case SR_TEXTURE_DATA_FORMAT_RGB_F16:    return GL_RGB16F;
            case SR_TEXTURE_DATA_FORMAT_RGB_F32:    return GL_RGB32F;
            case SR_TEXTURE_DATA_FORMAT_RGBA_8:     return GL_RGBA8;
            case SR_TEXTURE_DATA_FORMAT_RGBA_I8:    return GL_RGBA8I;
            case SR_TEXTURE_DATA_FORMAT_RGBA_I16:   return GL_RGBA16I;
            case SR_TEXTURE_DATA_FORMAT_RGBA_I32:   return GL_RGBA32I;
            case SR_TEXTURE_DATA_FORMAT_RGBA_UI8:   return GL_RGBA8UI;
            case SR_TEXTURE_DATA_FORMAT_RGBA_UI16:  return GL_RGBA16UI;
            case SR_TEXTURE_DATA_FORMAT_RGBA_UI32:  return GL_RGBA32UI;
            case SR_TEXTURE_DATA_FORMAT_RGBA_F16:   return GL_RGBA16F;
            case SR_TEXTURE_DATA_FORMAT_RGBA_F32:   return GL_RGBA32F;
        }

        SR_CORE_WARNING("Invalid texture data format given to converter, defaulting to GL_RGBA8");
        return GL_RGBA8;
    }

    GLenum getGlDepthFunc(SR_COMPARISON_FUNC func){
        switch (func){
            case SR_COMPARISON_FUNC_NEVER:           return GL_NEVER;
            case SR_COMPARISON_FUNC_LESS:            return GL_LESS;
            case SR_COMPARISON_FUNC_EQUAL:           return GL_EQUAL;
            case SR_COMPARISON_FUNC_LESS_EQUAL:      return GL_LEQUAL;
            case SR_COMPARISON_FUNC_GREATER:         return GL_GREATER;
            case SR_COMPARISON_FUNC_NOT_EQUAL:       return GL_NOTEQUAL;
            case SR_COMPARISON_FUNC_GREATER_EQUAL:   return GL_GEQUAL;
            case SR_COMPARISON_FUNC_ALWAYS:          return GL_ALWAYS;
            default: {
                SR_CORE_WARNING("Invalid depth func given to converter, defaulting to GL_LESS");
                return GL_LESS;
            }
        }
    }

    GLint getGlTextureFilter(SR_TEXTURE_FILTER filter){
        switch (filter) {
            case SR_TEXTURE_FILTER_LINEAR:  return GL_LINEAR;
            case SR_TEXTURE_FILTER_POINT:   return GL_NEAREST;
            default: {
                SR_CORE_WARNING("Invalid texture filter given to converter, defaulting to GL_LINEAR");
                return GL_LINEAR;
            }
        }
    }

    GLint getGlTextureWrap(SR_TEXTURE_WRAP wrap){
        switch(wrap){
            case SR_TEXTURE_WRAP_REPEAT:        return GL_REPEAT;
            case SR_TEXTURE_WRAP_MIRROR_REPEAT: return GL_MIRRORED_REPEAT;
            case SR_TEXTURE_WRAP_CLAMP_EDGE:    return GL_CLAMP_TO_EDGE;
            case SR_TEXTURE_WRAP_CLAMP_BORDER:  return GL_CLAMP_TO_BORDER;
            default: {
                SR_CORE_WARNING("Invalid texture wrap given to converter, defaulting to GL_REPEAT");
                return GL_REPEAT;
            }
        }
    }
}
