#pragma once

#include<assert.h>
template<typename T>
class CArr
{
private:
	T*			m_pData;
	int			m_iCount;
	int			m_iMaxCount;

public:
	void Push_back(const T& _Data);
	void resize(int _iResizeCount);
	T& operator[] (int idx);
	int data() { return m_pData; }
	T& size() { return m_iCount; }
	int capacity() { return m_iMaxCount; }
	class iterator;
	//레퍼런스는 기존 데이터가 있는 경우에 사용하지만 
	//이 경우에는 지역변수를 전달하기 때문에 
	//레퍼런스타입을 사용하지 않음
	iterator begin();
	iterator end();

public:
	//생성자와 소멸자는 public으로 생성해야 함
	CArr();
	~CArr();
	//class 내부 새로 class 생성
	//inner class
	//내부 데이터를 가르키는 변수 생성
	//내부 class도 template임
	//inner class가 포함된 class의 private 멤버 접근이 가능함
	class iterator
	{
	private:
		CArr* m_pArr; //iterator가 가리킬 데이터를 관리하는 가변배열 주소
		T* m_pData;
		int m_iIdx;
		

	public:
		T& operator* ()
		{
			//iterator가 알고있는 시작주소와 가변배열이 알고있는 주소가 달라진경우 오류처리
			//iterator가 end iterator 인 경우 오류처리
			if (m_pData != m_pArr->m_pData || -1 == m_iIdx)
				assert(nullptr);
			return m_pData[m_iIdx];
		}
		iterator& operator++ ()
		{
			return *this;
		}
		iterator& operator-- ()
		{
			return *this;
		}

	public:
		iterator()
			:m_pArr(nullptr)  
			,m_pData(nullptr)
			, m_iIdx(-1)
		{

		}
		iterator(CArr* _pArr, T* _pData, int iIdx)
			:m_pArr(_pArr)
			,m_pData(_pData)
			,m_iIdx(iIdx)
		{

		}
		~iterator()
		{

		}
	};
};


//주석 설정						: Ctrl + k , c 
//지정한 주석 해제		: Ctrl + k , u
//Alt Drag
//Alt Enter							: 정의만들기
//Ctal+tap							: 파일 간 이동
template<typename T>
CArr<T>::CArr()
	: m_pData(nullptr)
	, m_iCount(0)
	, m_iMaxCount(2)
{
	//m_pInt = (int*)malloc(sizeof(int) * 2);
	m_pData = new T[2];
}
template<typename T>
CArr<T>::~CArr()
{
	delete[] m_pData;
	m_iCount = 0;
	m_iMaxCount = 0;
}
template<typename T>
void CArr<T>::Push_back(const T& _Data)
{
	if (m_iMaxCount <= m_iCount)
	{
		//재할당
		resize(m_iMaxCount * 2);
	}
	//데이터 추가
	m_pData[m_iCount++] = _Data;
}
template<typename T>
void CArr<T>::resize(int _iResizeCount)
{

	if (m_iMaxCount >= _iResizeCount)
	{
		assert(nullptr);
	}
	//1. _iResizeCount 만큼 공간 할당
	T* pNew = new T[_iResizeCount];

	//2. 기존 데이터 복사
	for (int i = 0; i < m_iCount; ++i)
	{
		pNew[i] = m_pData[i];
	}

	//3. 기존 메모리 해제
	delete[] m_pData;

	//4. 배열이 새로 할당된 공간을 가리키게 함
	m_pData = pNew;

	//5. MaxCount 변경점 적용
	m_iMaxCount = _iResizeCount;
}
template<typename T>
T& CArr<T>::operator[](int idx)
{
	return m_pData[idx];
}

template<typename T>
typename CArr<T>::iterator CArr<T>::begin()
{
	/*
	iterator iter;
	iter.m_pData = this->m_pData;
	iter.m_iIdx = 0;
	*/
	/*
	iterator iter(m_pData, 0);
	return iter;
	*/
	if (0 == m_iCount)
		return iterator(this, m_pData, -1); //데이터가 없는 경우 begin() == end()

	//임시객체 생성하자마자 반환
	return iterator(this,this->m_pData,0);
}
template<typename T>
typename CArr<T>::iterator CArr<T>::end()
{
	return iterator(this, this->m_pData, -1);
}
