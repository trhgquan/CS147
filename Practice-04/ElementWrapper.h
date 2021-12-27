#pragma once
#ifndef _ELEMENT_WRAPPER_H_
#define _ELEMENT_WRAPPER_H_

//Wrapper for each element in array

template<class T>
class ElementWrapper {

private:	//private attribute
	T _value;	//value of the element
	int _leftInversionCount = 0;	
	int _rightInversionCount = 0;

public:	//getter & setter
	T value() { return _value; }
	int leftInversionCount() { return _leftInversionCount; }
	int rightInversionCount() { return _rightInversionCount; }
	
	void setValue(int value) { _value = value; }
	void setLeftInv(int value) { _leftInversionCount = value; }
	void setRightInv(int value) { _rightInversionCount = value; }

public: //public utilities

	void IncLeftInv() { ++_leftInversionCount; }
	void IncRightInv() { ++_rightInversionCount; }


	void reset() {
		_leftInversionCount = 0;
		_rightInversionCount = 0;
	}

public:	//constructor & destructor
	ElementWrapper()
	{
		//do nothing
	}

	~ElementWrapper()
	{
		//do nothing
	}
};

#endif // !_ELEMENT_WRAPPER_H_




