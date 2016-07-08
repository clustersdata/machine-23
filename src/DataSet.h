#ifndef JONO_DATASET_H
#define JONO_DATASET_H

// includes from standard library
#include <vector>
#include <memory>

// includes from jono library


namespace jono {

//! Class to manage data sets, slicing, subsets, etc.
class DataSet {
public:
    using dvec = std::vector<double>;

    struct DataPoint {
        dvec x;
        dvec y;
    };

    using data_ptr = std::shared_ptr<DataPoint>;
    using pvec = std::vector<data_ptr>;

public:
    //! Default constructor
    DataSet();

    //! Move constructor
    DataSet(DataSet&& other);

    //! Copy constructor
    DataSet(const DataSet& other);

    //! assignment operator
    DataSet &operator=(const DataSet& other);

    //! Destructor
    ~DataSet();

    //! Sort according to selected feature
    void sort(int feature);

    //! Return a subset of dataset by slicing
    DataSet slice(int begin, int end);

    //! Return the array of data points
    pvec& getPoints();

    //! Return average value of response
    dvec averageResponse();

    //! Return number of features
    int nfeatures();

    //! Return number of responses
    int nresponses();


    pvec::const_iterator cbegin() const;
    pvec::const_iterator cend() const;

private:
    //! Vector of pointers to data points
    pvec points;

};



} // namespace jono

#endif // JONO_DATASET_H
