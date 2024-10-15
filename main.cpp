#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "listheader.h"
#include "XArrayListDemo.h"
#include "DLinkedListDemo.h"
#include "ann/xtensor_lib.h"
#include "ann/dataset.h"
#include "dataloader.h"
using namespace std;


void tensor_status() {
    xt::xarray<xt::xarray<double>> data;

    cout << "INITIALIZED/CREATED WITH A TENSOR: dimension!=0, shape is not empty " << endl;
    data = xt::arange(125).reshape({3,3,3});
    xt::xarray<double> temp = { 3, 3, 4, 5 };
    data[1] = temp;
    cout << "A non-empty tensor: (dimension!=0)" << endl;
    cout << "data: " << endl << data << endl;
    cout << "data.dimension(): " << data.dimension() << endl;
    cout << "data.size(): " << data.size() << endl << endl;
    cout << xt::view(data, 0) << endl << endl;    
    cout << data(1) << endl << endl;
    xt::xarray<double> v = { 900, 990, 999 };
    xt::view(data,  1) = v;
    cout << data << endl << endl;

}

string shape2str(xt::svector<size_t> vec) {
    stringstream ss;
    ss << "(";
    for (int idx = 0; idx < vec.size(); idx++) {
        ss << vec.at(idx) << ", ";
    }
    string res = ss.str();
    if (vec.size() > 1) res = res.substr(0, res.rfind(','));
    else res = res.substr(0, res.rfind(' '));
    return res + ")";
}

int positive_index(int idx, int size) {
    if (idx < 0) return idx = size + idx;
    return idx;
}

void case_data_wo_label_1() {
    xt::xarray<int> X = xt::arange<int>(10 * 4).reshape({ 10, 4 });
    xt::xarray<int> t;
    //Show X and t
    cout << "############################################" << endl;
    cout << "#CASE: data WITHOUT label" << endl;
    cout << "############################################" << endl;
    cout << "ORIGINAL data and label:" << endl;
    cout << "X.shape: " << shape2str(X.shape()) << endl;
    cout << "X: " << endl << X << endl;
    cout << "t.shape: " << shape2str(t.shape()) << endl;
    cout << "t: " << endl << t << endl;
    cout << "=================================" << endl;

    //Create TensorDataset and DataLoader
    TensorDataset<int, int> ds(X, t);
    int batch_size = 3;
    bool shuffle = false, drop_last = false;
    int seed;
    DataLoader<int, int>* pLoader;

    cout << "Loading (1): with shuffle=false:" << endl;
    cout << "################################" << endl;
    shuffle = false;
    seed = -1;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    int batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    cout << endl << endl;
    delete pLoader;

    cout << "Loading (2): with shuffle=true + no seed (seed < 0):" << endl;
    cout << "when seed < 0: DO NOT call xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = -1;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    cout << endl << endl;
    delete pLoader;

    cout << "Loading (3): with shuffle=true + no seed (seed < 0):" << endl;
    cout << "when seed < 0: DO NOT call xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = -1;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    cout << endl << endl;
    delete pLoader;
    cout << "NOTE: Loading (2) and (3): DO NOT CALL seed; so results are different." << endl;
    cout << endl << endl;

    cout << "Loading (4): with shuffle=true + with seed (seed >= 0):" << endl;
    cout << "when seed >= 0: CALL xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = 100;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    delete pLoader;

    cout << "Loading (5): with shuffle=true + with seed (seed >= 0):" << endl;
    cout << "when seed >= 0: CALL xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = 100;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    delete pLoader;
    cout << "NOTE: Loading (4) and (5): CALL xt::random::seed and use SAME seed => same results." << endl;
    cout << endl << endl;
}

void case_data_wi_label_1() {
    xt::xarray<int> X = xt::arange<int>(10 * 4).reshape({ 10, 4 });
    xt::xarray<int> t = xt::arange<int>(10);
    //Show X and t
    cout << "############################################" << endl;
    cout << "#CASE: data WITH label" << endl;
    cout << "WHEN label is available: " << endl;
    cout << "\tAssignment-1: ASSUME that dimension-0 on data = dimension-0 on label" << endl;
    cout << "############################################" << endl;
    cout << "ORIGINAL data and label:" << endl;
    cout << "X.shape: " << shape2str(X.shape()) << endl;
    cout << "X: " << endl << X << endl;
    cout << "t.shape: " << shape2str(t.shape()) << endl;
    cout << "t: " << endl << t << endl;
    cout << "=================================" << endl;

    //Create TensorDataset and DataLoader
    TensorDataset<int, int> ds(X, t);
    int batch_size = 3;
    bool shuffle = false, drop_last = false;
    int seed;
    DataLoader<int, int>* pLoader;

    cout << "Loading (1): with shuffle=false:" << endl;
    cout << "################################" << endl;
    shuffle = false;
    seed = -1;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    int batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    cout << endl << endl;
    delete pLoader;

    cout << "Loading (2): with shuffle=true + no seed (seed < 0):" << endl;
    cout << "when seed < 0: DO NOT call xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = -1;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    cout << endl << endl;
    delete pLoader;

    cout << "Loading (3): with shuffle=true + no seed (seed < 0):" << endl;
    cout << "when seed < 0: DO NOT call xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = -1;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    cout << endl << endl;
    delete pLoader;
    cout << "NOTE: Loading (2) and (3): DO NOT CALL seed; so results are different." << endl;
    cout << endl << endl;

    cout << "Loading (4): with shuffle=true + with seed (seed >= 0):" << endl;
    cout << "when seed >= 0: CALL xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = 100;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    delete pLoader;
    cout << endl << endl;

    cout << "Loading (5): with shuffle=true + with seed (seed >= 0):" << endl;
    cout << "when seed >= 0: CALL xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = 100;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    delete pLoader;
    cout << "NOTE: Loading (4) and (5): CALL xt::random::seed and use SAME seed => same results." << endl;
    cout << endl << endl;
}

void case_batch_larger_nsamples() {
    int nsamples = 10;
    xt::xarray<int> X = xt::arange<int>(nsamples * 4).reshape({ nsamples, 4 });
    xt::xarray<int> t;
    //Show X and t
    cout << "############################################" << endl;
    cout << "#CASE: data WITHOUT label" << endl;
    cout << "############################################" << endl;
    cout << "ORIGINAL data and label:" << endl;
    cout << "X.shape: " << shape2str(X.shape()) << endl;
    cout << "X: " << endl << X << endl;
    cout << "t.shape: " << shape2str(t.shape()) << endl;
    cout << "t: " << endl << t << endl;
    cout << "=================================" << endl;

    //Create TensorDataset and DataLoader
    TensorDataset<int, int> ds(X, t);
    int batch_size = 15; //15 > 10 => 10/15 = 0
    bool shuffle = false, drop_last = false;
    int seed;
    DataLoader<int, int>* pLoader;

    cout << "Loading (1): with shuffle=false:" << endl;
    cout << "Number of samples: " << nsamples << endl;
    cout << "batch-size: " << batch_size << endl;
    cout << "=> number of batches to be processed: " << int(nsamples / batch_size) << endl;
    cout << "################################" << endl;
    shuffle = false;
    seed = -1;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    int batch_idx = 0;
    for (auto batch : *pLoader) {
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:" << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    cout << "NUMBER OF BATCHES PROCESSED: " << batch_idx << endl;
    delete pLoader;


}
int main(int argc, char** argv) {
    case_data_wo_label_1();

    //tensor_status();
}

