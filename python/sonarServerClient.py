
import Ice
from sonarHelper import sonar

communicator = Ice.initialize(['--Ice.Config=../config/client.config'])
prx = communicator.propertyToProxy("SonarServer.Proxy")
server = sonar.SonarServerPrx.checkedCast( prx )

server.onStatus( [ sonar.ServerStatus( [0], [0], 'id1', [ sonar.Status.OK] ) ] )
server.onStatus( [ sonar.ServerStatus( [0], [0], 'id3', [ sonar.Status.OK] ) ] )
server.onStatus( [ sonar.ServerStatus( [0], [0], 'id5', [ sonar.Status.OK] ) ] )
server.onStatus( [ sonar.ServerStatus( [0], [0], 'id4', [ sonar.Status.OK] ) ] )
server.onStatus( [ sonar.ServerStatus( [0], [0], 'id2', [ sonar.Status.OK] ) ] )

server.onStatus( [ sonar.ServerStatus( [0], [0], x, [ sonar.Status.OK] ) for x in ['id1','id2','id3','id4','id5' ]  ] )
server.onStatus( [ sonar.ServerStatus( [0], [0], x, [ sonar.Status.WARN] ) for x in ['id1','id2' ]  ] )
server.onStatus( [ sonar.ServerStatus( [0], [0], x, [ sonar.Status.ERROR] ) for x in ['id5' ]  ] )

print [ (x.id,x.status[0]) for x in server.getStatuses()] 
#server.reset()

