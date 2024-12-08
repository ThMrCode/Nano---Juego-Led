#pragma once

template <typename T>
class Tensor
{
private:
	T* data;
	uint8_t n_size;
public:
	Tensor();
	Tensor(uint8_t size_);
	Tensor(const Tensor& other);
	~Tensor();
	T& operator[](uint8_t index);
	bool operator==(const Tensor& other) const;
	Tensor<T>& operator=(const Tensor& other);
	void resize(uint8_t s);
	void resize_value(uint8_t s, T value);
	void push(T d);
	void push_if_not(T d);
	void pop(uint8_t pot);
	int indexOf(T d);
	uint8_t size();
};

template<typename T>
inline Tensor<T>::Tensor() : data(nullptr), n_size(0)
{
}

template <typename T>
inline Tensor<T>::Tensor(uint8_t size_): data(nullptr), n_size(0)
{
	this->resize(size_);
}

template<typename T>
inline Tensor<T>::Tensor(const Tensor& other) : data(nullptr), n_size(0)
{
	this->resize(other.n_size);
	for (uint8_t i = 0; i < this->n_size; i++)
	{
		this->data[i] = other.data[i];
	}
}

template<typename T>
inline Tensor<T>::~Tensor()
{
    if(data != nullptr) delete[] data;
}

template<typename T>
T& Tensor<T>::operator[](uint8_t index)
{
	return this->data[index];
}

template<typename T>
inline bool Tensor<T>::operator==(const Tensor& other) const
{
	bool value_return = true;
	if (this->n_size != other.n_size) value_return = false;
	else {
		for (uint8_t i = 0; i < this->n_size; i++) {
			if (this->data[i] != other.data[i]) {
				value_return = false;
				break;
			}
		}
	}
	return value_return;
}

template <typename T>
inline Tensor<T> &Tensor<T>::operator=(const Tensor &other)
{
	if(this != &other) {
		this->resize(other.n_size);
		for (uint8_t i = 0; i < this->n_size; i++)
		{
			this->data[i] = other.data[i];
		}
	}
	return *this;
}

template<typename T>
void Tensor<T>::resize(uint8_t s)
{
	if (this->data != nullptr) delete[] this->data;
	this->data = new T[s];
	this->n_size = s;
}

template<typename T>
inline void Tensor<T>::resize_value(uint8_t s, T value)
{
	this->resize(s);
	for (uint8_t i = 0; i < this->n_size; i++)
	{
		this->data[i] = value;
	}
}

template<typename T>
inline void Tensor<T>::push(T d)
{
	T* aux;
	aux = new T[this->n_size + 1];
	for (uint8_t i = 0; i < this->n_size; i++)
	{
		aux[i] = this->data[i];
	}
	aux[this->n_size] = d;
	if (this->data != nullptr) delete[]this->data;
	this->data = aux;
	this->n_size++;
}

template<typename T>
inline void Tensor<T>::push_if_not(T d)
{
	bool value_not_find = true;
	for (uint8_t i = 0; i < this->n_size; i++)
	{
		if (this->data[i] == d) {
			value_not_find = false;
			break;
		}
	}
	if (value_not_find) this->push(d);
}

template<typename T>
inline void Tensor<T>::pop(uint8_t pot)
{
	T* temp = new T[this->n_size - 1];
	uint8_t counter = 0;
	for (uint8_t i = 0; i < this->n_size; i++)
	{
		if(i != pot) {
			temp[counter] = this->data[i];
			counter++;
		}
	}
	if (this->data != nullptr) delete[] this->data;
	this->data = temp;
	this->n_size -= 1;
}

template <typename T>
inline int Tensor<T>::indexOf(T d)
{
	int index_return = -1;
	for (uint8_t i = 0; i < this->n_size; i++)
	{
		if(this->data[i] == d) {
			index_return = i;
			break;
		}
	}
    return index_return;
}

template <typename T>
uint8_t Tensor<T>::size()
{
	return this->n_size;
}
