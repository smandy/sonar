#pragma once

#include "Ice/Identity.ice"
#include "Ice/BuiltinSequences.ice"

module sonar {
enum Status { OK, WARN, ERROR };

sequence<Status> StatusSeq;

struct ServerStatus {
::Ice::LongSeq      lastReport;
::Ice::LongSeq      started;
string    id;
StatusSeq status;
};

sequence<ServerStatus> ServerStatusSeq;
    
struct Image {
ServerStatusSeq stats;
};

struct Update {
ServerStatusSeq updates;
};

interface SonarServerListener {
["amd"] void onImage( Image img);
["amd"] void onUpdate( Update upd);
};
    
interface SonarServer {
// Received from clients
["amd"] void onStatus( ServerStatusSeq s);

["amd"] void addListener( SonarServerListener listener);
["amd"] void removeListener( SonarServerListener listener);
        
["amd"] void addListenerByIdent( Ice::Identity listener);
["amd"] void removeListenerByIdent( Ice::Identity listener);

// Diagnostic - just for debug
["amd"] ServerStatusSeq getStatuses();
};
};
