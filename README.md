# machine
author: Jonathan Fisher

email: j.fisher@fz-juelich.de, jonathan.m.fisher@gmail.com

license: GPL, see LICENSE


This is a personal project intended to help me learn the details of some standard machine learning algorithms. Initially I will implement a few naive algorithms, and then gradually introduce more complexity. As the code evolves, I will try to add (in comments) references to relevant journal articles or textbooks.

This project is not intended to replace, or to compete with any other open-source machine learning projects (e.g. xgboost, scikit-learn, etc.). It is strictly for educational and entertainment purposes.

The basic aim of this project is to use C++ features such as inheritance and operator overloading to allow complex learners to be built out of very simple ones. The basic building block is an ILearner, which is a very simple interface. As a concrete implementation, there is for example the AverageLearner class, which does nothing but compute the average value of a dataset. A TreeLearner can be constructed by recursively partitioning the dataset, with an ILearner attached to each node. Abstract learners can be added together (via operator overloading), to produce an instance of EnsembleLearner. Fitting an EnsembleLearner simply chooses an appropriate weighted linear combination of the ILearners in the ensemble, etc.

## Continuous integration status
| CI | branch | status |
|----|---|-----|
| Travis | master |[![Build Status](https://travis-ci.org/jmf1sh/machine.svg?branch=master)](https://travis-ci.org/jmf1sh/machine)| 
| AppVeyor | master | [![Build status](https://ci.appveyor.com/api/projects/status/g4nyvry4rrorw33u?svg=true)](https://ci.appveyor.com/project/jmf1sh/machine)|
| CodeDocs | master | [![Docs status](https://codedocs.xyz/jmf1sh/machine.svg)](https://codedocs.xyz/jmf1sh/machine)
