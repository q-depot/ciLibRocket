/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "ciLibRocketRenderInterface.h"
#include <Rocket/Core.h>
#include "cinder/gl/Vbo.h"

#define GL_CLAMP_TO_EDGE 0x812F

using namespace ci;
using namespace ci::app;
using namespace std;


class MeshWrapper {

public:
    
    MeshWrapper() {}
    
    ~MeshWrapper() {}
    
    ci::gl::VboMesh                 mMesh;
	
    Rocket::Core::TextureHandle     mTexture;
    
};


void ciLibRocketRenderInterface::RenderGeometry( Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation )
{
    ci::gl::pushMatrices();
    
    ci::gl::translate( translation.x, translation.y );

    /*
     bool normalizedTex = ofGetUsingNormalizedTexCoords();
	if(texture)
    {
		if(!normalizedTex)
			ofEnableNormalizedTexCoords();
		((ofImage*)texture)->bind();
	}
*/
    
    vector<uint32_t>    vbo_indices;
	vector<Vec3f>       vbo_positions;
	vector<Vec2f>       vbo_texCoords;
	vector<ColorA>      vbo_colors;
    
    gl::VboMesh::Layout layout;
	layout.setStaticIndices();
	layout.setStaticPositions();
	layout.setStaticTexCoords2d();
    layout.setStaticColorsRGBA();
    
    ci::gl::VboMesh mesh = gl::VboMesh( num_vertices, num_indices, layout, GL_TRIANGLES );
    
	for( int i=0; i < num_vertices; i++ )
    {
		vbo_positions.push_back( Vec3f( vertices[i].position.x, vertices[i].position.y, 0 ) );
		vbo_colors.push_back( ColorA( vertices[i].colour.red/255.f, vertices[i].colour.green/255.f, vertices[i].colour.blue/255.f, vertices[i].colour.alpha/255.f ) );
		vbo_texCoords.push_back( Vec2f( vertices[i].tex_coord.x, vertices[i].tex_coord.y ) );
	}

	for( int i=0; i<num_indices; i++ )
		vbo_indices.push_back( indices[i] );
    
	mesh.bufferPositions( vbo_positions );
	mesh.bufferIndices( vbo_indices );
    mesh.bufferColorsRGBA( vbo_colors );
	mesh.bufferTexCoords2d( 0, vbo_texCoords );
    
    gl::draw( mesh );
//	
//	if(!normalizedTex)
//		ofDisableNormalizedTexCoords();
	
    ci::gl::popMatrices();
}


Rocket::Core::CompiledGeometryHandle ciLibRocketRenderInterface::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle texture)
{
    MeshWrapper *wrapper = new MeshWrapper();
    
    vector<uint32_t>    vbo_indices;
	vector<Vec3f>       vbo_positions;
	vector<Vec2f>       vbo_texCoords;
	vector<ColorA>      vbo_colors;
    
    gl::VboMesh::Layout layout;
	layout.setStaticIndices();
	layout.setStaticPositions();
	layout.setStaticTexCoords2d();
	layout.setStaticColorsRGBA();
    
    ci::gl::VboMesh mesh = gl::VboMesh( num_vertices, num_indices, layout, GL_TRIANGLES );
    
	for( int i=0; i < num_vertices; i++ )
    {
		vbo_positions.push_back( Vec3f( vertices[i].position.x, vertices[i].position.y, 0 ) );
		vbo_colors.push_back( ColorA( vertices[i].colour.red/255.f, vertices[i].colour.green/255.f, vertices[i].colour.blue/255.f, vertices[i].colour.alpha/255.f ) );
		vbo_texCoords.push_back( Vec2f( vertices[i].tex_coord.x, vertices[i].tex_coord.y ) );
	}
    
	for( int i=0; i<num_indices; i++ )
		vbo_indices.push_back( indices[i] );
    
	mesh.bufferPositions( vbo_positions );
	mesh.bufferIndices( vbo_indices );
    mesh.bufferColorsRGBA( vbo_colors );
	mesh.bufferTexCoords2d( 0, vbo_texCoords );
    
    wrapper->mTexture = texture;
    wrapper->mMesh = mesh;

	return (Rocket::Core::CompiledGeometryHandle) wrapper;
}


void ciLibRocketRenderInterface::RenderCompiledGeometry( Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation )
{
    gl::pushMatrices();
    
    gl::translate( translation.x, translation.y );
	
	MeshWrapper* wrapper = (MeshWrapper*)geometry;
	
//	bool normalizedTex = ofGetUsingNormalizedTexCoords();
	
	if( wrapper->mTexture )
    {
//		ofEnableAlphaBlending();
//		if(!normalizedTex)
//			ofEnableNormalizedTexCoords();
//		((gl::Texture*)wrapper.mTexture)->bind();
	}
	
    gl::draw( wrapper->mMesh );
//	
//	if(wrapper->texture){
//		((ofImage*)wrapper->texture)->unbind();
//		ofDisableAlphaBlending();
//	}
//	
//	if(!normalizedTex)
//		ofDisableNormalizedTexCoords();
	
    gl::popMatrices();
}


void ciLibRocketRenderInterface::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
//	delete ((MeshWrapper*)geometry)->mMesh;
}


void ciLibRocketRenderInterface::EnableScissorRegion(bool enable)
{
	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}


void ciLibRocketRenderInterface::SetScissorRegion(int x, int y, int width, int height)
{
	//ofViewport(x, ofGetHeight() - (y + height), width, height);
//	glScissor(x, ofGetHeight() - (y + height), width, height);
}


bool ciLibRocketRenderInterface::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
//	ofImage* img = new ofImage();
//	img->loadImage(source.CString());
//	texture_handle = (Rocket::Core::TextureHandle) img;
//	return img->isAllocated();
    return false;
}


bool ciLibRocketRenderInterface::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
//	ofImage* img = new ofImage();
//	img->setFromPixels(source, source_dimensions.x, source_dimensions.y, OF_IMAGE_COLOR_ALPHA, false);
//	texture_handle = (Rocket::Core::TextureHandle) img;
//	return img->isAllocated();
    return false;
}


void ciLibRocketRenderInterface::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
//	delete (ofImage*)texture_handle;
}
