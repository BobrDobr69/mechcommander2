//===========================================================================//
// Copyright (C) Microsoft Corporation. All rights reserved.                 //
//===========================================================================//

#pragma once

#ifndef MLR_MLR_I_C_DET_TMESH_HPP
#define MLR_MLR_I_C_DET_TMESH_HPP

//#include <mlr/mlr.hpp>
//#include <mlr/mlr_i_det_tmesh.hpp>
//#include <mlr/mlr_i_c_det_pmesh.hpp>

namespace MidLevelRenderer {

	//##########################################################################
	//###### MLRIndexedTriMesh with color no lighting and detail texture #######
	//##########################################################################


	class MLR_I_C_DeT_TMesh:
		public MLR_I_DeT_TMesh
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Initialization
		//
	public:
		static void __stdcall InitializeClass(void);
		static void __stdcall TerminateClass(void);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Constructors/Destructors
		//
	protected:
		MLR_I_C_DeT_TMesh(
			ClassData *class_data,
			Stuff::MemoryStream *stream,
			int32_t version
			);
		~MLR_I_C_DeT_TMesh();

	public:
		MLR_I_C_DeT_TMesh(ClassData *class_data=MLR_I_C_DeT_TMesh::DefaultData);

		static MLR_I_C_DeT_TMesh*
			Make(
			Stuff::MemoryStream *stream,
			int32_t version
			);

		void
			Save(Stuff::MemoryStream *stream);

	public:
#if COLOR_AS_DWORD
		virtual void
			SetColorData(
			pcuint32_t array,
			int32_t point_count
			);
		virtual void
			GetColorData(
			uint32_t **array,
			pint32_t point_count
			);
#else
		virtual void
			SetColorData(
			const Stuff::RGBAColor *array,
			int32_t point_count
			);
		virtual void
			GetColorData(
			Stuff::RGBAColor **array,
			pint32_t point_count
			);
#endif

		virtual void
#if COLOR_AS_DWORD
			PaintMe(pcuint32_t paintMe);
#else
			PaintMe(const Stuff::RGBAColor *paintMe);
#endif

		virtual int32_t	TransformAndClip(Stuff::Matrix4D *, MLRClippingState, GOSVertexPool*,bool=false);

		virtual void
			TransformNoClip(Stuff::Matrix4D*, GOSVertexPool*,bool=false);

		void
			Copy(
			MLR_I_C_TMesh*,
			MLRState detailState,
			float xOff,
			float yOff,
			float xFac,
			float yFac
			);

		bool
			Copy(MLR_I_C_DeT_PMesh*);

		virtual void
			HurtMe(const Stuff::LinearMatrix4D&, float radius);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Class Data Support
		//
	public:
		static ClassData* DefaultData;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Testing
		//
	public:
		void TestInstance(void) const;

		virtual int32_t
			GetSize()
		{ 
			Check_Object(this);
			int32_t ret = MLR_I_DeT_TMesh::GetSize();
			ret += colors.GetSize();

			return ret;
		}

	protected:
#if COLOR_AS_DWORD
		Stuff::DynamicArrayOf<uint32_t> colors;	// Base address of color list 
		Stuff::DynamicArrayOf<uint32_t> *actualColors;
#else
		Stuff::DynamicArrayOf<Stuff::RGBAColor> colors;	// Base address of color list 
		Stuff::DynamicArrayOf<Stuff::RGBAColor> *actualColors;
#endif
	};

	MLR_I_C_DeT_TMesh*
		CreateIndexedTriCube_Color_NoLit_DetTex(float, MLRState*);
	MLRShape*
		CreateIndexedTriIcosahedron_Color_NoLit_DetTex (
		IcoInfo&,
		MLRState*,
		MLRState*
		);

}
#endif
