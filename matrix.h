#ifndef MY_MATRIX_MATRIX_H
#define MY_MATRIX_MATRIX_H

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Matrix {
public:
    class Row {
        friend class Matrix;
        // by adding this we provide acces to all private members for the friend class;
    private:
        // making it public will allow us to construct this object outside of the matrix, that will be strange. We
        // narrow an ability to construct this object to the matrix itself so we make it private
        Row(Matrix* owner, size_t row_num) : owner_(owner), row_num_(row_num) {
        }

    public:
        // notes about return data type is the same as getElement()
        T& operator[](size_t col_j) {
            return owner_->GetElement(row_num_, col_j);
        }

        const T& operator[](size_t col_j) const {
            return owner_->GetElement(row_num_, col_j);
        }

    private:
        Matrix* owner_;
        size_t row_num_;
    };

public:
    class ConstRow {
        friend class Matrix;

        ConstRow(const Matrix* owner, size_t row_num) : owner_(owner), row_num_(row_num) {
        }

    public:
        const T& operator[](size_t col_j) const {
            return owner_->GetElement(row_num_, col_j);
        }

    private:
        const Matrix* owner_;
        size_t row_num_;
    };

public:
    // default conctructor (parameter less)
    Matrix()
        : row_num_(0)  // actually here an initilazer contrcutor works here
          ,
          col_num_(0),
          matrix_(nullptr) {
    }

    Matrix(const Matrix& other);

    Matrix(size_t row_num, size_t col_num);

    Matrix(size_t row_num, size_t col_num, T def_value);

    void Init(size_t row_num, size_t col_num);

    void Crop(size_t new_col_num, size_t new_row_num);

    inline void MySwap(Matrix& m1, Matrix& m2);

    ~Matrix() {
        delete[] matrix_;
    }

    Row operator[](size_t row_i) {
        return Row(this, row_i);
    }

    ConstRow operator[](size_t row_i) const {
        return ConstRow(this, row_i);
    }

public:
    size_t GetRowNum() const {
        return row_num_;
    }

    size_t GetColNum() const {
        return col_num_;
    }

    const T* GetStorage() const {
        return matrix_;
    }

public:
    size_t GetOffset(size_t row_i, size_t col_j) const {
        return row_i * col_num_ + col_j;
    }

    T& GetElement(size_t row_i, size_t col_j) {
        return matrix_[GetOffset(row_i, col_j)];
    }

    const T& GetElement(size_t row_i, size_t col_j) const {
        return matrix_[GetOffset(row_i, col_j)];
    }

public:
    bool operator==(const Matrix& rhs) const;

    // Matrix operator + (Matrix& rhs) const;
private:
    size_t row_num_{};  // initilize here is okay but mostly appear for primitive Datatypes
    size_t col_num_{};
    T* matrix_;
};

// non member function for operator !=. Since this nonmember function is markeda as inline we can put its inplementation
// here
template <typename T>
inline bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    return !(lhs == rhs);
}

// шаблоны
// норм
template <typename T>
Matrix<T>::Matrix(size_t row_num, size_t col_num) : row_num_(row_num), col_num_(col_num), matrix_(nullptr) {
    if (row_num == 0 && col_num == 0) {
        return;
    }

    if (row_num == 0 || col_num == 0) {
        // bad!
        throw std::invalid_argument("one of the paramets is 0 while other is not 0");
    }
    matrix_ = new T[row_num_ * col_num_];
}

template <typename T>
Matrix<T>::Matrix(size_t row_num, size_t col_num, T def_value) : Matrix(row_num, col_num) {
    for (size_t i = 0; i < row_num * col_num; ++i) {
        matrix_[i] = def_value;
    }
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& rhs) const {
    if (row_num_ != rhs.row_num_ || col_num_ != rhs.col_num_) {
        return false;
    }

    for (size_t i = 0; i < row_num_ * col_num_; ++i) {
        if (matrix_[i] != rhs.matrix_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
inline void Matrix<T>::MySwap(Matrix& m1, Matrix& m2) {
    std::swap(m1.matrix_, m2.matrix_);
    std::swap(m1.row_num_, m2.row_num_);
    std::swap(m1.col_num_, m2.col_num_);
}

template <typename T>
void Matrix<T>::Crop(size_t new_col_num, size_t new_row_num) {
    new_col_num = std::min(new_col_num, GetColNum());
    new_row_num = std::min(new_row_num, GetRowNum());
    Matrix<T> new_matrix = Matrix<T>(new_row_num, new_col_num);
    for (size_t i = 0; i < new_row_num; i++) {
        if (i >= GetRowNum()) {
            continue;
        }
        for (size_t j = 0; j < new_col_num; j++) {
            if (j >= GetColNum()) {
                continue;
            }
            new_matrix[i][j] = GetElement(i, j);
        }
    }
    MySwap(*this, new_matrix);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : Matrix(other.GetRowNum(), other.GetColNum()) {
    for (size_t i = 0; i < row_num_; i++) {
        for (size_t j = 0; j < col_num_; j++) {
            matrix_[GetOffset(i, j)] = other.GetElement(i, j);
        }
    }
}

template <typename T>
void Matrix<T>::Init(size_t row_num, size_t col_num) {
    Matrix new_matrix = Matrix(row_num, col_num);
    MySwap(*this, new_matrix);
}

#endif
