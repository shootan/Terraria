#include "Object.h"

bool Object::initWithCollision(float _range, CGSize _BoundSize)
{
	if( !CCSprite::init() ) return false;
	m_fCloseDistance	= _range;
	m_cgBoundSize		= _BoundSize;
	return true;
}

bool Object::PointInRect(CGPoint _point)
{
	return CGRect::CGRectContainsPoint( this->getBoundBox(), _point );
}

bool Object::RectInRect(CGRect _rect)
{
	return CGRect::CGRectIntersectsRect( this->getBoundBox(), _rect );
}

CGRect Object::getBoundBox()
{
	CGRect rc;
	rc.origin	= this->getPosition();
	rc.size		= m_cgBoundSize;
	return rc;
}

