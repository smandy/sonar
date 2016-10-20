#include <iostream>
#include "sonar.h"
#include "Ice/Ice.h"
#include "IceStorm/IceStorm.h"
#include <memory>
#include <vector>
#include "ruleLoader.h"

class SonarServerImpl : public sonar::SonarServer {
    Ice::CommunicatorPtr communicator;
    IceStorm::TopicPrx   topic;
    std::set<sonar::SonarServerListenerPrx> listeners;
    std::vector<RulePtr> rules;
    
public:
    SonarServerImpl( Ice::CommunicatorPtr _communicator) : communicator( _communicator) {
        auto topicPrx = IceStorm::TopicManagerPrx::checkedCast( communicator->propertyToProxy("IceStorm.TopicManager"));
        auto subject = communicator->getProperties()->getProperty("Sonar.Topic");
        try {
            topic = topicPrx->retrieve(subject);
        } catch( IceStorm::NoSuchTopic &) {
            topic = topicPrx->create(subject);
        }
        listeners.insert(sonar::SonarServerListenerPrx::uncheckedCast(topic->getPublisher()));
    }

    virtual void addListenerByIdent_async(const ::sonar::AMD_SonarServer_addListenerByIdentPtr&,
                                          const ::Ice::Identity& ident,
                                          const ::Ice::Current& = ::Ice::Current()) {
    }

    virtual void removeListenerByIdent_async(const ::sonar::AMD_SonarServer_removeListenerByIdentPtr&,
                                             const ::Ice::Identity&,
                                             const ::Ice::Current& = ::Ice::Current()) {
    }

    std::vector<sonar::ServerStatus> statuses;
    void onStatus_async(const ::sonar::AMD_SonarServer_onStatusPtr& cb,
                        const ::sonar::ServerStatusSeq& stats,
                        const ::Ice::Current& = ::Ice::Current()) { 
        static thread_local sonar::ServerStatus finder;
        for ( const auto& stat : stats ) {
            std::cout << "On status " << stat.id << std::endl;
            const auto x = std::lower_bound( begin(statuses),
                                       end(statuses),
                                       stat,
                                       []( auto& a, auto& b) {
                                           return a.id < b.id;
                                       });
            if (x == end( statuses ) || x->id != stat.id) {
                // Insert
                statuses.insert(x, stat);
            } else {
                // Update
                *x = stat;
            }
        }
        cb->ice_response();
    };

    virtual void getStatuses_async(
                                   const ::sonar::AMD_SonarServer_getStatusesPtr& cb,
                                   const ::Ice::Current& = ::Ice::Current()) {
        cb->ice_response( sonar::ServerStatusSeq {
                begin( statuses),
                    end(statuses) } );
    };
    
    virtual void
    addListener_async(const ::sonar::AMD_SonarServer_addListenerPtr &,
                      const ::sonar::SonarServerListenerPtr &,
                      const ::Ice::Current & = ::Ice::Current()) {
        std::cout << "AddListener" << std::endl;
    };
    
    virtual void
    removeListener_async(const ::sonar::AMD_SonarServer_removeListenerPtr &,
                         const ::sonar::SonarServerListenerPtr &,
                         const ::Ice::Current & = ::Ice::Current()) {
        std::cout << "RemoveListener" << std::endl;
    };

    virtual void loadConfig_async(const ::sonar::AMD_SonarServer_loadConfigPtr& cb,
                                  const ::std::string& fn,
                                  const ::Ice::Current& = ::Ice::Current()) {
        std::cout << "LoadConfig" << std::endl;
        auto rules = RuleLoader::parseRules(fn);
        cb->ice_response(rules.size());
    };
};

int main(int argc, char *argv[]) {
  std::cout << "Make communicator" << std::endl;
  auto communicator = Ice::initialize(argc, argv);
  std::cout << "Make server" << std::endl;
  auto server = std::make_unique<SonarServerImpl>(communicator);
  std::cout << "Make adapter" << std::endl;
  auto adapter = communicator->createObjectAdapter("SonarServer");
  std::cout << "Add impl to adapter" << std::endl;
  // Liveness of server ensured by scope of main
  auto prx =
      adapter->add(server.get(), communicator->stringToIdentity("server"));
  std::cout << "Activate adpater" << std::endl;
  adapter->activate();
  std::cout << "Wait for shutdown" << std::endl;
  communicator->waitForShutdown();
  std::cout << "Shutdown - exiting" << std::endl;
};
