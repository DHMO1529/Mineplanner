/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_RELATIVECOORDINATE_JUCEHEADER__
#define __JUCE_RELATIVECOORDINATE_JUCEHEADER__

#include "../../graphics/geometry/juce_Path.h"
#include "../../graphics/geometry/juce_Rectangle.h"
#include "../../../maths/juce_Expression.h"


//==============================================================================
/**
    Expresses a coordinate as a dynamically evaluated expression.

    @see RelativePoint, RelativeRectangle
*/
class JUCE_API  RelativeCoordinate
{
public:
    //==============================================================================
    /** Creates a zero coordinate. */
    RelativeCoordinate();
    RelativeCoordinate (const Expression& expression);
    RelativeCoordinate (const RelativeCoordinate& other);
    RelativeCoordinate& operator= (const RelativeCoordinate& other);

    /** Creates an absolute position from the parent origin on either the X or Y axis.

        @param absoluteDistanceFromOrigin   the distance from the origin
    */
    RelativeCoordinate (double absoluteDistanceFromOrigin);

    /** Recreates a coordinate from a string description.
        The string will be parsed by ExpressionParser::parse().
        @param stringVersion    the expression to use
        @see toString
    */
    RelativeCoordinate (const String& stringVersion);

    /** Destructor. */
    ~RelativeCoordinate();

    bool operator== (const RelativeCoordinate& other) const noexcept;
    bool operator!= (const RelativeCoordinate& other) const noexcept;

    //==============================================================================
    /** Calculates the absolute position of this coordinate.

        You'll need to provide a suitable Expression::Scope for looking up any coordinates that may
        be needed to calculate the result.
    */
    double resolve (const Expression::Scope* evaluationScope) const;

    /** Returns true if this coordinate uses the specified coord name at any level in its evaluation.
        This will recursively check any coordinates upon which this one depends.
    */
    bool references (const String& coordName, const Expression::Scope* evaluationScope) const;

    /** Returns true if there's a recursive loop when trying to resolve this coordinate's position. */
    bool isRecursive (const Expression::Scope* evaluationScope) const;

    /** Returns true if this coordinate depends on any other coordinates for its position. */
    bool isDynamic() const;

    //==============================================================================
    /** Changes the value of this coord to make it resolve to the specified position.

        Calling this will leave the anchor points unchanged, but will set this coordinate's absolute
        or relative position to whatever value is necessary to make its resultant position
        match the position that is provided.
    */
    void moveToAbsolute (double absoluteTargetPosition, const Expression::Scope* evaluationScope);

    /** Returns the expression that defines this coordinate. */
    const Expression& getExpression() const         { return term; }


    //==============================================================================
    /** Returns a string which represents this coordinate.
        For details of the string syntax, see the constructor notes.
    */
    String toString() const;

    //==============================================================================
    /** A set of static strings that are commonly used by the RelativeCoordinate class.

        As well as avoiding using string literals in your code, using these preset values
        has the advantage that all instances of the same string will share the same, reference-counted
        String object, so if you have thousands of points which all refer to the same
        anchor points, this can save a significant amount of memory allocation.
    */
    struct Strings
    {
        static const String parent;         /**< "parent" */
        static const String left;           /**< "left" */
        static const String right;          /**< "right" */
        static const String top;            /**< "top" */
        static const String bottom;         /**< "bottom" */
        static const String x;              /**< "x" */
        static const String y;              /**< "y" */
        static const String width;          /**< "width" */
        static const String height;         /**< "height" */
    };

    struct StandardStrings
    {
        enum Type
        {
            left, right, top, bottom,
            x, y, width, height,
            parent,
            unknown
        };

        static Type getTypeOf (const String& s) noexcept;
    };

private:
    //==============================================================================
    Expression term;
};


#endif   // __JUCE_RELATIVECOORDINATE_JUCEHEADER__
