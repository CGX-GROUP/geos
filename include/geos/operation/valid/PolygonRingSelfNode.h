/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2021 Paul Ramsey <pramsey@cleverelephant.ca>
 * Copyright (C) 2021 Martin Davis
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/

#pragma once

#include <geos/export.h>

#include <geos/geom/Coordinate.h>

#include <memory>


namespace geos {      // geos.
namespace operation { // geos.operation
namespace valid {     // geos.operation.valid

class GEOS_DLL PolygonRingSelfNode {
    using CoordinateXY = geos::geom::CoordinateXY;

private:

    CoordinateXY nodePt;
    const CoordinateXY* e00;
    const CoordinateXY* e01;
    const CoordinateXY* e10;
    const CoordinateXY* e11;


public:

    PolygonRingSelfNode(
        const CoordinateXY& p_nodePt,
        const CoordinateXY* p_e00,
        const CoordinateXY* p_e01,
        const CoordinateXY* p_e10,
        const CoordinateXY* p_e11)
        : nodePt(p_nodePt)
        , e00(p_e00)
        , e01(p_e01)
        , e10(p_e10)
        , e11(p_e11)
        {}

    /**
    * The node point.
    *
    * @return
    */
    const CoordinateXY* getCoordinate() const {
        return &nodePt;
    }

    /**
    * Tests if a self-touch has the segments of each half of the touch
    * lying in the exterior of a polygon.
    * This is a valid self-touch.
    * It applies to both shells and holes.
    * Only one of the four possible cases needs to be tested,
    * since the situation has full symmetry.
    *
    * @param isInteriorOnRight whether the interior is to the right of the parent ring
    * @return true if the self-touch is in the exterior
    */
    bool isExterior(bool isInteriorOnRight) const;

};

} // namespace geos.operation.valid
} // namespace geos.operation
} // namespace geos

