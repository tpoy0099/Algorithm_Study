#ifndef Utility_sMatrix_H
#define Utility_sMatrix_H

/*
数组模板
模拟c++中双下标数组M[][]取值功能
实现常用的清空,覆盖,复制,查询大小等功能
*/

#ifndef NULL
#define NULL 0
#endif

template <class Item_Type> 
class sMatrixRow
{
public:
    sMatrixRow() {
        m_pItems = NULL;
        m_NumOfItems = 0;
        m_Capacity = 0;
    }

    sMatrixRow(const sMatrixRow<Item_Type> &sTargetRow) {
        m_pItems = NULL;
        m_NumOfItems = 0;
        m_Capacity = 0;
        *this = sTargetRow;
    }

    ~sMatrixRow() {
        delete [] m_pItems;
    }

    void Init(size_t i) {
        if (i > 0) {
            if (m_Capacity >= i) {
                m_NumOfItems = i;
            }
            else {
                delete [] m_pItems;
                m_NumOfItems = i;
                m_Capacity = i;
                m_pItems = new Item_Type[m_Capacity];
                if (!m_pItems)
                    throw "sMatrixRow::Init()\n";
            }     
        }
    }

    void Initialize(size_t i, Item_Type DefValue) {
        Init(i);
        Cover(DefValue);
    }

    sMatrixRow<Item_Type>& operator = (const sMatrixRow<Item_Type> &sTargetRow) {
        Init(sTargetRow.Size());
        for (size_t i = 0; i < sTargetRow.Size(); ++i)
            m_pItems[i] = sTargetRow.Get(i);
        
        return *this;
    }

    Item_Type& operator[] (size_t i) {
        if (i < m_NumOfItems)
            return m_pItems[i];
        else
            throw "Index out of range !\n";
    }

    void Cover(Item_Type v) {
        for (size_t i = 0; i < m_NumOfItems; ++i)
            m_pItems[i] = v;
    }

    Item_Type Get(size_t i) const {
        if (i < m_NumOfItems)
            return m_pItems[i];
        else
            throw "Index out of range !\n";
    }

    size_t Size() const {
        return m_NumOfItems; 
    }

    bool Empty() const {
        return m_NumOfItems > 0 ? false : true;
    }

private:
    Item_Type* m_pItems;
    size_t m_NumOfItems;
    size_t m_Capacity;
};

template <class Item_Type> 
class sMatrix
{
public:
    sMatrix() {
        m_pDataRows = NULL;
        m_NumOfRows = 0;
        m_NumOfColumns = 0;
    }

    sMatrix(const sMatrix<Item_Type> &sTarget) {
        m_pDataRows = NULL;
        m_NumOfRows = 0;
        m_NumOfColumns = 0;
        *this = sTarget;
    }

    ~sMatrix() {
       delete [] m_pDataRows;
    }

    bool Initialize(size_t row, size_t col, Item_Type DefValue) {
        if (row > 0 && col > 0) {
            if (m_NumOfRows != row || m_NumOfColumns != col) {
                delete [] m_pDataRows;
                m_NumOfRows = row;
                m_NumOfColumns = col;
                m_pDataRows = new sMatrixRow<Item_Type>[m_NumOfRows];
            }

            if (m_pDataRows) {
                for (size_t i = 0; i < m_NumOfRows; ++i) {
                    m_pDataRows[i].Init(m_NumOfColumns);
                    m_pDataRows[i].Cover(DefValue);
                }
                return true;
            }
        }
        return false;
    }

    //generate a new Matrix from target area
    //copy range : [fRow, tRow] ,[fCol, tCol] : include head and tail element
    bool InitFrom(const sMatrix<Item_Type> &tMatrix, size_t fRow, size_t tRow, size_t fCol, size_t tCol) {
        if (tMatrix.nRows() > tRow && tMatrix.nCols() > tCol) {
            if (m_NumOfRows != tRow-fRow+1 || m_NumOfColumns != tCol-fCol+1) {
                m_NumOfRows    = tRow - fRow + 1;
                m_NumOfColumns = tCol - fCol + 1;
                delete [] m_pDataRows;
                m_pDataRows = new sMatrixRow<Item_Type>[m_NumOfRows];
            }
            
            if (m_pDataRows) {
                size_t i, j, fR = fRow, fC = fCol;
                for (i = 0; i < m_NumOfRows; ++i, ++fR, fC = fCol) {
                    m_pDataRows[i].Init(m_NumOfColumns);
                    for (j = 0; j < m_NumOfColumns; ++j, ++fC)
                        m_pDataRows[i][j] = tMatrix.Get(fR, fC);
                }
                return true;
            }
        }
        return false;
    }

    void Cover(Item_Type newvalue) {
        for (size_t i = 0; i < m_NumOfRows; ++i)
            m_pDataRows[i].Cover(newvalue);
    }

    sMatrix<Item_Type>& operator = (const sMatrix<Item_Type> &tMatrix) {
        InitFrom(tMatrix, 0, tMatrix.nRows()-1, 0, tMatrix.nCols()-1);
        return *this;
    }

    sMatrixRow<Item_Type>& operator[] (size_t r) {
        if (r < m_NumOfRows)
            return m_pDataRows[r];
        else
            throw "Index out of range !\n";
    }

    const sMatrixRow<Item_Type>& GetRow(size_t r) const{
        if (r < m_NumOfRows)
            return m_pDataRows[r];
        else
            throw "Index out of range !\n";
    }

    Item_Type Get(size_t r, size_t c) const{
        if (r < m_NumOfRows && c < m_NumOfColumns)
            return m_pDataRows[r][c];
        else 
            throw "Index out of range !\n";
    }

    size_t nRows() const{
        return m_NumOfRows;
    }

    size_t nCols() const{
        return m_NumOfColumns;
    }

    bool Empty() const {
        if (m_NumOfRows * m_NumOfColumns > 0)
            return false;
        return true;
    }

private:
    sMatrixRow<Item_Type>* m_pDataRows;
    size_t m_NumOfRows;
    size_t m_NumOfColumns;
};

#endif