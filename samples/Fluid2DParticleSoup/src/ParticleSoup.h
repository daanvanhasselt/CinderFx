/*

Copyright (c) 2012-2013 Hai Nguyen
All rights reserved.

Distributed under the Boost Software License, Version 1.0.
http://www.boost.org/LICENSE_1_0.txt
http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt

*/

#pragma once

#include <vector>
//
#include "cinder/Color.h"
#include "cinder/Rect.h"
#include "cinder/Vector.h"
using ci::Colorf;
using ci::Rectf;
using ci::Vec2f;
//
#include "cinderfx/Fluid2D.h"
using cinderfx::Fluid2D;

/**
 * \class Particle
 *
 */
class Particle {
public:

	Particle() : mAccel( 0, 0 ) {}
	Particle( const Vec2f& aPos, float aLife, const Colorf& aColor ) 
		: mPos( aPos ), mPrevPos( aPos ), mAccel( 0, 0 ), mLife( aLife ), mAge( 0 ), mColor( aColor ) {}

	Vec2f&			pos() { return mPos; }
	const Vec2f&	pos() const { return mPos; }
	void			setPos( const Vec2f& aPos ) { mPos = aPos; mPrevPos = aPos; }
	void			addForce( const Vec2f& aForce ) { mAccel += aForce; }

	float			life() const { return mLife; }
	float			age() const { return mAge; }

	const Colorf&	color() const { return mColor; }
	void			setColor( const Colorf& aColor ) { mColor = aColor; }

	void			reset( const Vec2f& aPos, float aLife, const Colorf& aColor );

	void			update( float simDt, float ageDt );

private:
	Vec2f			mPos;
	Vec2f			mPrevPos;
	Vec2f			mAccel;
	float			mLife;
	float			mAge;
	Colorf			mColor;
};

/**
 * \class ParticleSoup
 *
 */
class ParticleSoup {
public:

	ParticleSoup() : mColor( ci::hsvToRGB( ci::Vec3f( 0.0f, 1.0f, 1.0f ) ) ) {}

	int				numParticles() const { return (int)mParticles.size(); }
	Particle&		at( int n ) { return *( mParticles.begin() + (size_t)n ); }
	const Particle&	at( int n ) const { return *( mParticles.begin() + (size_t)n ); }
	void			append( const Particle& aParticle ) { mParticles.push_back( aParticle ); }

	const Colorf&	color() const { return mColor; }
	void			setColor( const Colorf& aColor ) { mColor = aColor; }

	void			setup( Fluid2D* aFluid );
	void			update();
	void			draw();

private:
	Fluid2D*				mFluid;
	std::vector<Particle>	mParticles;
	Colorf					mColor;
};
