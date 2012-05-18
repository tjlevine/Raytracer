#include "PrimitiveFactory.h"

const float PrimitiveFactory::NaN = std::numeric_limits<float>::quiet_NaN();

PrimitiveFactory::PrimitiveFactory()
{
    //params.reset();
    params.diff = 1.0f;
    params.refl = 0.0f;
}


PrimitiveFactory* PrimitiveFactory::diffusion( float d )    { params.diff  = d; return this; }
PrimitiveFactory* PrimitiveFactory::reflectivity( float r ) { params.refl  = r; return this; }
PrimitiveFactory* PrimitiveFactory::color( sf::Color c )    { params.col   = c; return this; }
PrimitiveFactory* PrimitiveFactory::pos( Vec3 p )           { params.pos_  = p; return this; }
PrimitiveFactory* PrimitiveFactory::name( std::string s )   { params.name_ = s; return this; }
PrimitiveFactory* PrimitiveFactory::radius( float r )       { params.rad   = r; return this; }
PrimitiveFactory* PrimitiveFactory::dist( float d )         { params.dist_ = d; return this; }
PrimitiveFactory* PrimitiveFactory::setScene( Scene* s )    { params.scene = s; return this; }

PrimitiveFactory* PrimitiveFactory::resetScene( Scene* newScene )
{
    params.scene = ( newScene != NULL ) ? newScene : NULL;
    return this;
}


Primitive* PrimitiveFactory::build( Primitive::PrimType pType )
{
    //clear anything we have in the passed pointer


    Primitive* ret;

    // depending on the type we were passed, create the primitive
    // and associated material
    switch ( pType )
    {
    case Primitive::SPHERE:
        //assert( memcmp( static_cast<const void*>( &rad ), static_cast<const void*>( &NaN ), sizeof( float ) ) != 0 );
        ret = new Sphere( params.pos_, params.rad );
        params.mat = new Material( params.col, params.diff, params.refl );

        if (  params.name_ != "" ) ret->setName( params.name_ );

        ret->setMaterial( params.mat );
        break;

    case Primitive::PLANE:
        //assert( memcmp( static_cast<const void*>( &dist_ ), static_cast<const void*>( &NaN ), sizeof( float ) ) != 0 );
        ret = new Plane( params.pos_, params.dist_ );
        params.mat = new Material( params.col, params.diff, params.refl );

        if ( params.name_ != "" ) ret->setName( params.name_ );

        ret->setMaterial( params.mat );
        break;

    }

    // add the primitive to the scene if we have one
    if( params.scene != NULL ) params.scene->addPrim( ret );

    // reset the variables so they are not re-used next time
    //diff = refl = rad = dist_ = NaN;

    return ret;
}
