//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

// This program is updated version of Sample_TempObstacles.h in original 'recastnavigation'


#ifndef RECASTSAMPLETEMPOBSTACLE_H
#define RECASTSAMPLETEMPOBSTACLE_H

#include "Sample.h"
#include "DetourNavMesh.h"
#include "Recast.h"
#include "ChunkyTriMesh.h"


class MySampleObstacles : public Sample
{
protected:
	bool m_keepInterResults;

	struct LinearAllocator* m_talloc;
	struct FastLZCompressor* m_tcomp;
	struct MeshProcess* m_tmproc;

	class dtTileCache* m_tileCache;
	
	float m_cacheBuildTimeMs;
	int m_cacheCompressedSize;
	int m_cacheRawSize;
	int m_cacheLayerCount;
	unsigned int m_cacheBuildMemUsage;
	
/* 	enum DrawMode
	{
		DRAWMODE_NAVMESH,
		DRAWMODE_NAVMESH_TRANS,
		DRAWMODE_NAVMESH_BVTREE,
		DRAWMODE_NAVMESH_NODES,
		DRAWMODE_NAVMESH_PORTALS,
		DRAWMODE_NAVMESH_INVIS,
		DRAWMODE_MESH,
		DRAWMODE_CACHE_BOUNDS,
		MAX_DRAWMODE
	};
	
	DrawMode m_drawMode; */
	
	int m_maxTiles;
	int m_maxPolysPerTile;
	float m_tileSize;
	
public:
	MySampleObstacles();
	virtual ~MySampleObstacles();
	
	virtual void handleSettings(const int &nodeSize = 2048);
	virtual void handleTools();
	virtual void handleDebugMode();
	virtual void handleRender();
	virtual void handleRenderOverlay(double* proj, double* model, int* view);
	virtual void handleMeshChanged(class InputGeom* geom);//, const std::vector<char> &areaTypes);
	virtual bool handleBuild(const std::vector<char> &areaTypes, const int &nodeSize = 2048);
	virtual void handleUpdate(const float dt);

	void getTilePos(const float* pos, int& tx, int& ty);
	
	void renderCachedTile(const int tx, const int ty, const int type);
	void renderCachedTileOverlay(const int tx, const int ty, double* proj, double* model, int* view);

	dtStatus addTempObstacle(const float *pos, const float &radi, const float &height);
	void removeTempObstacle(const float* sp, const float* sq);
	void clearAllTempObstacles();

	void saveAll(const char* path);
	void loadAll(const char* path);

private:
	// Explicitly disabled copy constructor and copy assignment operator.
	MySampleObstacles(const MySampleObstacles&);
	MySampleObstacles& operator=(const MySampleObstacles&);
	// maxNode size for NavMeshQuery 

	int rasterizeTileLayers(const int tx, const int ty, const rcConfig& cfg, struct TileCacheData* tiles, const int maxTiles,const std::vector<char> &areaTypes);
};


#endif // RECASTSAMPLETEMPOBSTACLE_H
