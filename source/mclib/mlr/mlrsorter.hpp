//===========================================================================//
// Copyright (C) Microsoft Corporation. All rights reserved.                 //
//===========================================================================//

#pragma once

#ifndef MLR_MLRSORTER_HPP
#define MLR_MLRSORTER_HPP

//#include <mlr/mlr.hpp>
//#include <mlr/mlrlight.hpp>
//#include <mlr/gosvertex.hpp>
//#include <mlr/gosvertex2uv.hpp>
//#include <mlr/gosvertexpool.hpp>

namespace MidLevelRenderer {

	class MLRPrimitive;
	class MLREffect;
	class GOSVertex;
	class DrawScreenQuadsInformation;

	struct SortAlpha;

	class SortData {
	public:
		SortData () 
		{ vertices = NULL; numVertices = 0; indices = NULL; 
		numIndices = 0; type = TriList; texture2 = 0; }

		void DrawTriList();
		void DrawTriIndexedList();
		void DrawPointCloud();
		void DrawLineCloud();
		void DrawQuads();

		int32_t LoadAlphaFromTriList(SortAlpha**);
		int32_t LoadAlphaFromTriIndexedList(SortAlpha**);
		int32_t LoadAlphaFromPointCloud(SortAlpha**);
		int32_t LoadAlphaFromLineCloud(SortAlpha**);
		int32_t LoadAlphaFromQuads(SortAlpha**);

		enum {
			TriList = 0,
			TriIndexedList,
			PointCloud,
			Quads,
			LineCloud,
			LastMode
		};

		typedef void (SortData::* DrawFunc)();
		typedef int32_t (SortData::* LoadSortAlphaFunc)(SortAlpha**);

		static DrawFunc Draw[LastMode];
		static LoadSortAlphaFunc LoadSortAlpha[LastMode];

		MLRState state;
		PVOIDvertices;
		int32_t	numVertices;
		puint16_t indices;
		int32_t numIndices;
		int32_t type;
		int32_t texture2;
	};


	class MLRPrimitiveBase;


#define CalDraw	


#ifdef CalDraw
	struct ToBeDrawnPrimitive {
		ToBeDrawnPrimitive();

		MLRPrimitiveBase *primitive;

		MLRState state;
		Stuff::Point3D cameraPosition;
		MLRClippingState clippingFlags;
		Stuff::Matrix4D shapeToClipMatrix;
		Stuff::LinearMatrix4D worldToShape;

		static GOSVertexPool *allVerticesToDraw;

		MLRLight* activeLights[Limits::Max_Number_Of_Lights_Per_Primitive];

		int32_t	nrOfActiveLights;
	};
#endif

	//##########################################################################
	//#########################    MLRSorter    ################################
	//##########################################################################

	class _declspec(novtable) MLRSorter :
		public Stuff::RegisteredClass
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Initialization
		//
	public:
		static void __stdcall InitializeClass(void);
		static void __stdcall TerminateClass(void);
		static ClassData* DefaultData;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Constructors/Destructors
		//
	public:
		MLRSorter(ClassData *class_data, MLRTexturePool*);
		~MLRSorter();

		virtual void AddPrimitive(MLRPrimitiveBase*, int32_t=0) = 0;
		virtual void AddEffect(MLREffect*, const MLRState&) = 0;
		virtual void AddScreenQuads(GOSVertex*, const DrawScreenQuadsInformation*) = 0;

		virtual void AddSortRawData(SortData*) = 0;

		virtual void
			DrawPrimitive(MLRPrimitiveBase*, int32_t=0);

		void
			SetTexturePool(MLRTexturePool *tp)
		{ Check_Object(this); Check_Object(tp); texturePool = tp; }

		bool
			SetDifferences(const MLRState& original, const MLRState& newer);

		//	starts the action
		virtual void RenderNow () = 0;

		//	resets the sorting
		virtual void Reset ();

		//	lets begin the dance
		virtual void StartDraw(const MLRState &default_state);

		//	enter raw data
		SortData*
			SetRawData
			(	PVOIDvertices, 
			int32_t numVertices,
			const MLRState& state,
			cint32_t& mode,
			int32_t tex2 = 0
			);

		SortData*
			SetRawIndexedData
			(	PVOID vertices, 
			int32_t numVertices, 
			puint16_t indices,
			int32_t numIndices,
			const MLRState& state, 
			cint32_t& mode,
			int32_t tex2 = 0
			);

		SortData*
			SetRawData(MLRPrimitiveBase*, int32_t=0 );

		//	Just scaling down a bit to keep z under 1.0f	
		void
			SetFarClipReciprocal(float fcr)
		{ Check_Object(this); farClipReciprocal = fcr*(1.0f-Stuff::SMALL); }

#ifdef CalDraw
		ToBeDrawnPrimitive*
			GetCurrentTBDP()
		{ Check_Object(this); return &drawData[lastUsedDraw]; }
		ToBeDrawnPrimitive*
			GetCurrentTBDP(int32_t index)
		{ Check_Object(this); Verify(index<lastUsedDraw); return &drawData[index]; }
		void
			IncreaseTBDPCounter();
#endif

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Testing
	//
	public:
		void TestInstance(void) const;

	protected:
		MLRState theCurrentState;
		MLRTexturePool *texturePool;

		int32_t lastUsedRaw;
		Stuff::DynamicArrayOf<SortData> rawDrawData; // Max_Number_Primitives_Per_Frame

		int32_t
			lastUsedInBucketNotDrawn[MLRState::PriorityCount];

#ifdef CalDraw
		int32_t lastUsedDraw;
		Stuff::DynamicArrayOf<ToBeDrawnPrimitive> drawData; // Max_Number_Primitives_Per_Frame
		Stuff::DynamicArrayOf<ToBeDrawnPrimitive*>  //, Max_Number_Primitives_Per_Frame + Max_Number_ScreenQuads_Per_Frame
			priorityBucketsNotDrawn[MLRState::PriorityCount];
#endif

		float
			farClipReciprocal;
	};

}
#endif
