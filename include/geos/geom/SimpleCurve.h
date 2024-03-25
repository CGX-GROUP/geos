/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 * Copyright (C) 2005 2006 Refractions Research Inc.
 * Copyright (C) 2011 Sandro Santilli <strk@kbt.io>
 * Copyright (C) 2024 ISciences, LLC
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/

#pragma once

#include <geos/geom/Curve.h>
#include <geos/geom/Geometry.h>

namespace geos {
namespace geom {

class GEOS_DLL SimpleCurve : public Curve {
public:

    std::unique_ptr<CoordinateSequence> getCoordinates() const override;

    /// Returns a read-only pointer to internal CoordinateSequence
    const CoordinateSequence* getCoordinatesRO() const;

    virtual const Coordinate& getCoordinateN(std::size_t n) const;

    /**
     * \brief
     * Take ownership of the CoordinateSequence managed by this geometry.
     * After releasing the coordinates, the geometry should be considered
     * in a moved-from state and should not be accessed.
     * @return this Geometry's CoordinateSequence.
     */
    std::unique_ptr<CoordinateSequence> releaseCoordinates();

    /**
     * \brief
     * Returns Dimension::False for a closed LineString,
     * 0 otherwise (LineString boundary is a MultiPoint)
     */
    int getBoundaryDimension() const override;

    /// Returns coordinate dimension.
    uint8_t getCoordinateDimension() const override;

    bool hasM() const override;

    bool hasZ() const override;

    /**
     * \brief
     * Returns a MultiPoint.
     * Empty for closed LineString, a Point for each vertex otherwise.
     */
    std::unique_ptr<Geometry> getBoundary() const override;

    bool isEmpty() const override;

    std::size_t getNumPoints() const override;

    virtual std::unique_ptr<Point> getPointN(std::size_t n) const;

    /// \brief
    /// Return the start point of the LineString
    /// or NULL if this is an EMPTY LineString.
    ///
    virtual std::unique_ptr<Point> getStartPoint() const;

    /// \brief
    /// Return the end point of the LineString
    /// or NULL if this is an EMPTY LineString.
    ///
    virtual std::unique_ptr<Point> getEndPoint() const;

    bool isClosed() const override;

    virtual bool isCoordinate(CoordinateXY& pt) const;

    bool equalsExact(const Geometry* other, double tolerance = 0)
    const override;

    bool equalsIdentical(const Geometry* other) const override;

    const CoordinateXY* getCoordinate() const override;

    const Envelope* getEnvelopeInternal() const override
    {
        return &envelope;
    }

    using Curve::apply_ro;
    using Curve::apply_rw;

    void apply_rw(const CoordinateFilter* filter) override;

    void apply_ro(CoordinateFilter* filter) const override;

    void apply_rw(CoordinateSequenceFilter& filter) override;

    void apply_ro(CoordinateSequenceFilter& filter) const override;

    /** \brief
     * Normalizes a SimpleCurve.
     *
     * A normalized simple curve
     * has the first point which is not equal to its reflected point
     * less than the reflected point.
     */
    void normalize() override;

    //was protected
    int compareToSameClass(const Geometry* ls) const override;


protected:

    SimpleCurve(const SimpleCurve& other);

    SimpleCurve(std::unique_ptr<CoordinateSequence>&& newCoords,
                const GeometryFactory& factory);

    Envelope computeEnvelopeInternal() const;

    void geometryChangedAction() override
    {
        envelope = computeEnvelopeInternal();
    }

    // TODO: hold value or shared_ptr instead of unique_ptr
    std::unique_ptr<CoordinateSequence> points;

    mutable Envelope envelope;

private:

    void normalizeClosed();
};

}
}
