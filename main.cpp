#include <iostream>
#include <vector>
#include <stdlib.h>
#include "AudioFile.h"

using namespace std;
static int Bsize =5;

vector<double> *myconvolution(vector<double> &A, vector <double > &B){
    int size = A.size()+B.size()-1;
    vector<double> *y=new vector<double>(size,0.0);
    int kappa;
    int keepo;
    for(auto i(0); i < size; ++i) {
        if (i>=B.size()-1){
            kappa = i-B.size()-1;
        }
        else{
            kappa=0;
        }
        if (i < A.size() - 1){
            keepo =i;
        }
        else {
            keepo = A.size() - 1;
        }
        for (auto j(kappa); j <= keepo; ++j) {
            if (!(i-j<0)) {
                (*y)[i] += (A[j] * B[i - j]);
            }
        }
    }
    return y;
}



int main() {
    cout << "Ergasia Ylopoihshs sunelhkshs " << endl;
    //Xrhsimopoiontas thn bibliothhkh pairnoume ta  arxeia wav kai dhmiourgoume 2 vector me ta samples tous
    AudioFile<double> pinkNoise;
    pinkNoise.load ("./pink_noise2.wav");
    AudioFile<double> sampleAudio;
    sampleAudio.load ("./sample_audio1.wav");
    vector<double> audiosample = sampleAudio.samples[0];
    //vector audiosample periexei ta samples tou arxeiou hxou
    vector<double> noise= pinkNoise.samples[0];
    //vector noise periexei ta samples tou thorubou
    cout<<"egine h eisagwgh stous vector "<<endl;
    vector<double> Y2;
    AudioFile<double> convolution1;
    AudioFile<double> convolution2;
    
    convolution1.setSampleRate(sampleAudio.getSampleRate());
    //vector me to convolution tou 2ou erwthmatos me ta audiofiles

    //Meros A1 me ta shmata A kai B
    vector<double> A;
    vector<double> B;
    vector<double> Y1;
    for (int i=0; i<Bsize; i++){
        B.push_back(0.2);
    }
    cout <<"Dwse to megethos tou shmatos A"<< endl;
    int N;
    cin>>N;
    double randomnumber;
    for (int i=0; i<N; i++){
        randomnumber = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        A.push_back(randomnumber);
        //cout<<randomnumber<<endl;
    }

    //prwth sunelhksh me A kai B
    Y1=*myconvolution(A,B);
    cout<<"apotelesma tou A1:"<<endl;
    for(int i =0; i<Y1.size();i++){
        cout <<Y1[i]<<endl;
    }

    //deuterh sunelhksh me sample kai noise
    convolution1.samples[0] =*myconvolution(audiosample,noise);
    convolution1.save("./pinkNoise_sampleAudio.wav");
    for (int i=0;i<pinkNoise.samples[0].size();i++){
        pinkNoise.samples[0][i]=static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    }
    convolution2.samples[0]=*myconvolution(audiosample,noise);
    convolution2.save("./whiteNoise_sampleAudio.wav");
    return 0;
}

