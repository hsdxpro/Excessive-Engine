#pragma once

#include <vector>
#include <limits>
#include "GraphicsEngine/IMesh.h"


class IVertexBuffer;
class IIndexBuffer;
class IGapi;

////////////////////////////////////////////////////////////////////////////////
// Notes
//
// Update this if you change something. Really.
//
// What is this class?
//	This class manages triangle mesh data.
//	Data is stored in vertex arrays and index arrays. For the index array, each
//	face has a material group, which is optional when rendering.
//
// Material groups
//	The id's are in an array. A i-th group is defined as the range [face[mtl_id[i]], face[mtl_id[i+1]]).
//	The (i+1)th element is in the list.
//
// Vertex format
//	A vertex element's format is always defined by it's semantic, though number
//	of components in the data vector may vary.
//	The data format can be accessed by the corresponding function.
//	Vertex elements may be distributed accross several streams.
//	A short 64 bit id can be used for hashing vertex formats.
// Format by semantic:
//	<semantic>	<type>	<width>	<num comp.>
//	POSITION	float	32		3
//	NORMAL		unorm	16		2
//	TEXi		unorm	16		changeable
//	COLORi		float	32		changeable
//	TANGENT		unorm	16		2
//	BITANGENT	unorm	16		2
//	Check packing function in .cpp for more info.
// Devs (internal behaviour):
//	The vertex elements are always in increasing order by their semantics (integer value of enum).
//	That is, a smaller semantic is either at smaller offset in the same buffer, or
//	in a different buffer with smaller index. Otherwise stream can have any number of elements.
//	These restriction allow the calculation of the 'short id', see its function.
//
////////////////////////////////////////////////////////////////////////////////


class Mesh : public graphics::IMesh
{
// public interface
public:
	// ctor, dtor
	Mesh(IGapi* gapi);
	~Mesh();

	////////////////////////////////////
	// interface

	// refcount / release
	void Acquire();
	void Release() override;

	// load
	void Load(const wchar_t* file_path) override; // it is supposed to return an error code

	// new modify
	bool Update(MeshData data) override;
	bool UpdateVertexData(const void* data, u32 offset, u32 size) override; // both params in bytes, format and total size considered the same

	void Reset() override;

	// interface end
	////////////////////////////////////

	// format of the data stored

	enum ElementType : u32 {
		// floating point types
		FLOAT = 1,
		HALF,
		// integer types
		SINT_32,
		UINT_32,
		SINT_16,
		UINT_16,
		SINT_8,
		UINT_8,
		// normalized integer types
		// signed: [-1.0f, 1.0f]
		// unsigned: [0.0f, 1.0f]
		SNORM_32,
		UNORM_32,
		SNORM_16,
		UNORM_16,
		SNORM_8,
		UNORM_8,
	};

	// helps lookup of vb by element semantic
	struct ElementInfo {
		int buffer_index; // in which buffer this semantic is
		unsigned offset; // offset from beginning of vertex
		ElementSemantic semantic;
		ElementType type;
		unsigned num_components;
	};

	struct VertexStream {
		IVertexBuffer* vb;
		u32 stride;
		u32 offset;
	};

	// Getters
	bool GetElementBySemantic(ElementInfo& info, ElementSemantic semantic) const;
	int GetElementsNum() const;
	const ElementInfo* GetElements() const;
	u64 GetElementConfigId() const;

	int GetNumVertexBuffers() { return num_streams; }
	const VertexStream* GetVertexBuffers() { return vertex_streams; }

	IIndexBuffer* GetIndexBuffer() { return index_buffer; }
	const std::vector<MaterialGroup>& GetMaterialIds() { return mat_ids; }

// internal mechanics
protected:
	// optimize data for gpu Drawing
	void optimize(void* vertex_data, u32 num_verts, int vertex_stride,
		u32* index_data, u32 num_indices,
		MaterialGroup* mat_ids, u32 num_mat_ids);

	// validate data for out-of-bound cases
	bool validate(u32 num_verts,
		u32* index_data, u32 num_indices,
		MaterialGroup* mat_ids, u32 num_mat_ids);




	// vertex packing
	void packVertices(ElementDesc* input_format, ElementInfo* output_format, int input_count, int output_count, void* input, void* output, u32 num_verts); // required size assumed

	// helpers with the format
	inline int GetFormatStrideInput(ElementDesc* elements, int num_elements) {
		int s = 0;
		for (int i = 0; i < num_elements; i++) {
			s += elements[i].num_components * sizeof(float);
		}
		return s;
	}
	inline int GetFormatStrideInternal(ElementInfo* elements, int num_elements) {
		int s = 0;
		for (int i = 0; i < num_elements; i++) {
			s += elements[i].num_components * GetElementTypeSize(elements[i].type);
		}
		return s;
	}
	inline int GetElementTypeSize(ElementType type) {
		switch (type) {
			case Mesh::FLOAT:
				return 4;
			case Mesh::HALF:
				return 2;
			case Mesh::SINT_32:
			case Mesh::UINT_32:
				return 4;
			case Mesh::SINT_16:
			case Mesh::UINT_16:
				return 2;
			case Mesh::SINT_8:
			case Mesh::UINT_8:
				return 1;
			case Mesh::SNORM_32:
			case Mesh::UNORM_32:
				return 4;
			case Mesh::SNORM_16:
			case Mesh::UNORM_16:
				return 2;
			case Mesh::SNORM_8:
			case Mesh::UNORM_8:
				return 1;
			default:
				return 0;
		}

	}
	ElementInfo GetBaseInfo(ElementDesc desc) {
		ElementSemantic semantic = desc.semantic;

		ElementInfo info;
		info.buffer_index = -1;
		info.offset = 0;
		if (semantic == POSITION) {
			info.num_components = 3;
			info.semantic = POSITION;
			info.type = FLOAT;
		}
		else if (semantic == NORMAL || semantic == TANGENT || semantic == BITANGENT) {
			info.num_components = 3;
			info.semantic = desc.semantic;
			info.type = FLOAT;
		}
		else if (COLOR0 <= semantic && semantic <= COLOR7) {
			info.num_components = desc.num_components;
			info.semantic = desc.semantic;
			info.type = FLOAT;
		}
		else if (TEX0 <= semantic && semantic <= TEX7) {
			info.num_components = desc.num_components;
			info.semantic = desc.semantic;
			info.type = FLOAT;
		}
		else {
			info.num_components = 0;
		}

		return info;
	}

	// mesh gpu resource
	VertexStream vertex_streams[20];
	u32 vertex_stream_content[20];

	ElementInfo elements[20];
	int num_streams;
	int num_elements;
	IIndexBuffer* index_buffer;
	std::vector<MaterialGroup> mat_ids;

// private vars
private:
	size_t refcount;
	IGapi* gapi;
};