
#ifndef CILIBROCKET_RENDERINTERFACE
#define CILIBROCKET_RENDERINTERFACE

#include <Rocket/Core/RenderInterface.h>
#include <Rocket/Core/Texture.h>
#include <Rocket/Core/Vertex.h>

class ciLibRocketRenderInterface : public Rocket::Core::RenderInterface {

public:
    
	ciLibRocketRenderInterface() {}
    
	~ciLibRocketRenderInterface() {}
    
    // Called by Rocket when it wants to render geometry that the application does not wish to optimise. Note that
    /// Rocket renders everything as triangles.
    /// @param[in] vertices The geometry's vertex data.
    /// @param[in] num_vertices The number of vertices passed to the function.
    /// @param[in] indices The geometry's index data.
    /// @param[in] num_indices The number of indices passed to the function. This will always be a multiple of three.
    /// @param[in] texture The texture to be applied to the geometry. This may be NULL, in which case the geometry is untextured.
    /// @param[in] translation The translation to apply to the geometry.
    void RenderGeometry( Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation );
    
    /// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
    /// If supported, this should be return a pointer to an optimised, application-specific version of the data. If
    /// not, do not override the function or return NULL; the simpler RenderGeometry() will be called instead.
    /// @param[in] vertices The geometry's vertex data.
    /// @param[in] num_vertices The number of vertices passed to the function.
    /// @param[in] indices The geometry's index data.
    /// @param[in] num_indices The number of indices passed to the function. This will always be a multiple of three.
    /// @param[in] texture The texture to be applied to the geometry. This may be NULL, in which case the geometry is untextured.
    /// @return The application-specific compiled geometry. Compiled geometry will be stored and rendered using RenderCompiledGeometry() in future calls, and released with ReleaseCompiledGeometry() when it is no longer needed.
    Rocket::Core::CompiledGeometryHandle CompileGeometry( Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);
    /// Called by Rocket when it wants to render application-compiled geometry.
    /// @param[in] geometry The application-specific compiled geometry to render.
    /// @param[in] translation The translation to apply to the geometry.
    void RenderCompiledGeometry( Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
    /// Called by Rocket when it wants to release application-compiled geometry.
    /// @param[in] geometry The application-specific compiled geometry to release.
    void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);
    
    /// Called by Rocket when it wants to enable or disable scissoring to clip content.
    /// @param[in] enable True if scissoring is to enabled, false if it is to be disabled.
    void EnableScissorRegion(bool enable);
    /// Called by Rocket when it wants to change the scissor region.
    /// @param[in] x The left-most pixel to be rendered. All pixels to the left of this should be clipped.
    /// @param[in] y The top-most pixel to be rendered. All pixels to the top of this should be clipped.
    /// @param[in] width The width of the scissored region. All pixels to the right of (x + width) should be clipped.
    /// @param[in] height The height of the scissored region. All pixels to below (y + height) should be clipped.
    void SetScissorRegion(int x, int y, int width, int height);
    
    /// Called by Rocket when a texture is required by the library.
    /// @param[out] texture_handle The handle to write the texture handle for the loaded texture to.
    /// @param[out] texture_dimensions The variable to write the dimensions of the loaded texture.
    /// @param[in] source The application-defined image source, joined with the path of the referencing document.
    /// @return True if the load attempt succeeded and the handle and dimensions are valid, false if not.
    bool LoadTexture( Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source );
    /// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
    /// @param[out] texture_handle The handle to write the texture handle for the generated texture to.
    /// @param[in] source The raw 8-bit texture data. Each pixel is made up of four 8-bit values, indicating red, green, blue and alpha in that order.
    /// @param[in] source_dimensions The dimensions, in pixels, of the source data.
    /// @return True if the texture generation succeeded and the handle is valid, false if not.
    bool GenerateTexture( Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions );
    /// Called by Rocket when a loaded texture is no longer required.
    /// @param texture The texture handle to release.
    void ReleaseTexture(Rocket::Core::TextureHandle texture);
    
    /// Returns the native horizontal texel offset for the renderer.
    /// @return The renderer's horizontal texel offset. The default implementation returns 0.
//    virtual float GetHorizontalTexelOffset();
    /// Returns the native vertical texel offset for the renderer.
    /// @return The renderer's vertical texel offset. The default implementation returns 0.
//    virtual float GetVerticalTexelOffset();
    
    /// Returns the number of pixels per inch.
    /// @returns The number of pixels per inch. The default implementation returns 100.
//    virtual float GetPixelsPerInch();
    
    /// Called when this render interface is released.
//    virtual void Release();

};

#endif

