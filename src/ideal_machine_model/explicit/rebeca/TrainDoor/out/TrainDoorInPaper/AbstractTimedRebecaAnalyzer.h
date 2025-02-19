#ifndef __ABSTRACT_TIMED_REBECA_ANALYZER_H__
#define __ABSTRACT_TIMED_REBECA_ANALYZER_H__

#include "TimedRebecaBFSHashmap.h"
#include "AbstractTimedActor.h"







    #include "EnvironmentActor.h"
    #include "ControllerActor.h"
    #include "TrainActor.h"
    #include "DoorActor.h"

#include <iostream>
#include <queue>

#define DEADLINE_MISSED 10

struct OpenBorderNode {
    TimedBFSState* state;
    int stateActiveBundleNumber;
    TIME_TYPE currentTime;

    OpenBorderNode& operator = (const OpenBorderNode& node2) {
        this->currentTime = node2.currentTime;
        this->state = node2.state;
		this->stateActiveBundleNumber = node2.stateActiveBundleNumber;
        return *this;
    }    
};

#define QUEUE_TYPE std::priority_queue<OpenBorderNode, std::vector<OpenBorderNode>, std::greater<OpenBorderNode> >

bool operator > (const OpenBorderNode& node1, const OpenBorderNode& node2);

class AbstractTimedRebecaAnalyzer {

protected:
	vector<AbstractTimedActor*> rebecs;
	TimedRebecaBFSHashmap *bfsStorage;
	OpenBorderNode current;
	// This variable is used for initialization of TimedBFSHashmap
	int hashmapSize;
	//Analysis of Timed Rebeca are based on BFS traversal which requires an open border queue
    QUEUE_TYPE openBorderQueue;
	int numberOfTimedBundles;
	int numberOfTransitions;
	int numberOfStates;
	
	ostream &analysisOutputStream;

	virtual void exportState(OpenBorderNode &current, ostream& outStream);
	virtual void exportTransition(OpenBorderNode &source, OpenBorderNode &destination, 
		string sender, string owner, string label, TIME_TYPE executionTime, TIME_TYPE shift, ostream& outStream);
	virtual void exportTransition(string source, string destination, 
		string sender, string owner, string label, TIME_TYPE executionTime, TIME_TYPE shift, ostream& outStream);
	OpenBorderNode storeRecentlyCreatedState(byte &result, TIME_TYPE &shift,
		TimedBFSState *parent, int parentBundleIndex, int executedRebecIndex);

    virtual void marshalRebecs(TimedRebecStateIndexType* node, TIME_TYPE *shift);
    virtual void unmarshalRebecs(TimedRebecStateIndexType* node, TIME_TYPE *shift);

	void changeOrder(int rebecId, int alternativesCounter);
	int getNumberOfAlternatives(int rebecId, TIME_TYPE executionTime);
	TIME_TYPE prepareWithNewState();
	
            	boolean _propDef_unLocked ();
        	boolean _propDef_Locked ();
        	boolean _propDef_Moving ();
        	boolean _propDef_Stop ();
    			void _propAssert_Assertion0 ();
	
	
public:

	AbstractTimedRebecaAnalyzer(std::ostream &out, int hashmapSize);
	virtual void instantiationPart();
};

#endif