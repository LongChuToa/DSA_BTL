/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */

#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/xtensor_lib.h"
#include "ann/dataset.h"

using namespace std;

template<typename DType, typename LType>
class DataLoader{
private:
    Dataset<DType, LType>* ptr_dataset;
    int dataset_len;
    Batch <DType, LType>* batch;
    xt::xarray<unsigned long> index_list;
    int batch_size;
    bool shuffle;
    bool drop_last;
    int m_seed;
    /*TODO: add more member variables to support the iteration*/
public:
    DataLoader(Dataset<DType, LType>* ptr_dataset,
        int batch_size,
        bool shuffle = true,
        bool drop_last = false, int seed = -1) :  batch_size(batch_size), shuffle(shuffle), drop_last(drop_last), m_seed(seed) {
        /*TODO: Add your code to do the initialization */
        this->ptr_dataset = ptr_dataset;
        dataset_len = ptr_dataset->len();
        int batch_num = dataset_len / batch_size;       //Calculate how many batch
        batch = new Batch<DType, LType>[batch_num];
        index_list = xt::arange(dataset_len);
        if (m_seed >= 0) {
            xt::random::seed(m_seed);
        }
        if (shuffle)    xt::random::shuffle(index_list);
        int index_cur = 0;
        for (int i = 0; i < batch_num; i++) {
            int index = index_list[index_cur];
            auto datas = ptr_dataset->get_data_shape();
            auto labels = ptr_dataset->get_label_shape();
            datas[0] = batch_num; labels[0] = batch_num;
            xt::xarray<DType> data = xt::empty<DType>(datas);
            xt::xarray<LType> label = xt::empty<LType>(labels);
            int label_dim = label.dimension();
            if (label_dim == 0) {
                if (!drop_last && i == batch_num - 1) {
                    int len = dataset_len - batch_size * batch_num;
                    datas[0] += len;
                    xt::xarray<DType> data = xt::empty<DType>(datas);
                    for (int j = 0; j < batch_size + len; j++)
                    {
                        xt::view(data, j) = ptr_dataset->getitem(index).getData();
                        index_cur++;
                        batch[i] = Batch<DType, LType>(data, 0);
                        index = index_list[index_cur];
                    }
                }
                else {
                    for (int j = 0; j < batch_size; j++) {
                        xt::view(data, j) = ptr_dataset->getitem(index).getData();
                        index_cur++;
                        batch[i] = Batch<DType, LType>(data, 0);
                        index = index_list[index_cur];
                    }
                }
            }
            else {
                if (!drop_last && i == batch_num - 1) {
                    int len = dataset_len - batch_size * batch_num;
                    datas[0] += len; labels[0] += len;
                    xt::xarray<DType> data = xt::empty<DType>(datas);
                    xt::xarray<LType> label = xt::empty<LType>(labels);
                    for (int j = 0; j < batch_size + len; j++)
                    {
                        xt::view(data, j) = ptr_dataset->getitem(index).getData();
                        xt::view(label, j) = ptr_dataset->getitem(index).getLabel();
                        index_cur++;
                        batch[i] = Batch<DType, LType>(data, label);
                        index = index_list[index_cur];
                    }
                }
                else {
                    for (int j = 0; j < batch_size; j++) {
                        xt::view(data, j) = ptr_dataset->getitem(index).getData();
                        xt::view(label, j) = ptr_dataset->getitem(index).getLabel();
                        index_cur++;
                        batch[i] = Batch<DType, LType>(data, label);
                        index = index_list[index_cur];
                    }
                }
            }
        }
    }
    virtual ~DataLoader(){}

    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////
    
    /*TODO: Add your code here to support iteration on batch*/
public:
    // Iterator: BEGIN
    class Iterator
    {
    private:
        int cursor;
        Batch<DType, LType> *batch_list;
    public:
        Iterator(Batch<DType, LType>* bList = 0, int index = 0) {
            this->batch_list = bList;
            this->cursor = index;
        }

        Iterator& operator=(const Iterator& iterator) {
            cursor = iterator.cursor;
            batch_list = iterator.batch_list;
            return *this;
        }

        bool operator!=(const Iterator& iterator) {
            return cursor != iterator.cursor;
        }

        Batch<DType, LType>& operator*() {
            return batch_list[cursor];
        }

        Iterator& operator++() {
            this->cursor++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        // Iterator: END
    };
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////

    Iterator begin() {
        return Iterator(this->batch, 0);
    }

    Iterator end() {
        return Iterator(this->batch, (dataset_len / batch_size));
    }
};


#endif /* DATALOADER_H */

