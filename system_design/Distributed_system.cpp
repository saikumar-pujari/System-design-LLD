What Is a Distributed System?
A Distributed System is a system where:
Multiple computers (nodes/servers) work together as one single system to achieve a common goal.
But to the user, it looks like ONE system, not multiple.

Imagine you're running a juice stall.
One person takes orders
One person cuts fruits
One person blends
One person delivers
To the customer → It feels like ONE shop, not four people doing different tasks.
That’s a distributed system.'

Why Do We Need Distributed Systems?
Because:
Need	                Reason
Scalability	            One machine can’t handle millions of users
Fault Tolerance        	If one server dies, the system still works
Performance	            Work is processed in parallel → Faster
High Availability	    Available 24×7 without downtime

Core Features of Distributed Systems
Feature	                    Meaning
Decentralization	        No single machine controls everything
Replication	                Data exists in multiple copies
Consistency Handling	    Keep all copies updated
Communication	            Machines communicate via network (HTTP, RPC, gRPC)
Transparency	            User doesn’t see the complexity

Easy Analogy: Pizza Shop Chain
Imagine Pizza Hut.
One store → OK for 10 customers
But for 10 lakh customers, one store cannot handle.
So they open multiple branches:
Bangalore branch
Kolkata branch
Mumbai branch

But they all follow:
✔ Same menu
✔ Same pricing
✔ Same system
To the customer → Looks like one Pizza Hut, but actually distributed.

Important Concepts in Distributed Systems

1️⃣  Load Balancer
Decides which server handles which request
Like a gatekeeper deciding which counter is free
Example:
User request → Load balancer → Server A or B or C

2️⃣ Replication
Same data stored in multiple servers so system doesn’t fail.
Example:
When you upload a photo to Instagram → It is stored in:
Mumbai server
Singapore backup
US replication
So even if 1 fails → data safe.

3️⃣ Sharding (Partitioning)
Split data into parts to improve performance.
Example:
Usernames A–M stored in one DB
Usernames N–Z stored in another DB

4️⃣ Consistency
All servers should agree on data.
But sometimes systems give speed > consistency (CAP theorem logic).
Example:
You send a message on WhatsApp:
Shows ✔ (sent)
Then after few ms shows ✔✔ (delivered)
Then after sync shows blue ✔✔ (read)
Updates come gradually → that's eventual consistency.'

=====================================================================================================================================================

Vertical Scaling (Scaling UP)
👉 Meaning: Increase the power of a single machine
You upgrade:
CPU
RAM
Storage
GPU
Example:
Your laptop lags → you increase RAM from 8GB → 16GB.
Same server, more power

Horizontal Scaling (Scaling OUT)
👉 Meaning: Add more machines instead of upgrading one.
and Need distributed coordination (+ consistency management).
Example:
Instead of using one supercomputer, use:
Server 1
Server 2
Server 3
...
all connected via distributed load balancing

Hint: start by vertical scaling and as user increase go for the horizontal scaling 

=====================================================================================================================================================
What Is Load Balancing?
👉 Load balancing is the technique of distributing incoming requests across multiple servers so no single server gets overloaded(uses constent hashing).
        X/n=1/n (x is server and n are users) or x1=m%n(m is the user)
Simple line:
Instead of one guy doing 100 tasks, divide it among many guys so everyone works smoothly.

Where Load Balancer Sits in Architecture:
    Client → Load Balancer → Server1
                                Server2
                                Server3

Types of Load Balancing Algorithms:
    1️⃣ Round Robin
    👉 Requests go to servers in order:
    A → B → C → A → B → C → A…
    Example:
    Requests: R1, R2, R3, R4, R5, R6
    Request	Server
    R1	A
    R2	B
    R3	C
    R4	A
    R5	B
    R6	C
    📍 Used when: All servers have equal power and tasks are similar.

    2️⃣ Weighted Round Robin
    👉 Some servers are stronger (more RAM/CPU), so they get more load.
    Example
    Server A weight = 3
    Server B weight = 1
    Distribution:
    A, A, A, B, A, A, A, B ...

    3️⃣ Least Connections
    👉 Assign request to the server with the fewest active users.
    Example:
    Server	Current Connections
    A	10
    B	4
    C	7
    Next request goes to → Server B
    📍 Used in chat apps, video calls where connection duration varies.

    4️⃣ IP Hashing
    👉 Same client always goes to the same server using a hashing function.
    Useful for:
    ✔ Session-based apps
    ✔ Gaming servers
    ✔ Sticky sessions (shopping cart)
    Example:
    User1 IP hashed → Server A
    User2 IP hashed → Server B
    So every time User1 comes → still Server A.

    5️⃣ Health-Based Load Balancing (Failover)
    If one server is dead, load balancer skips it.
    Example:
    Server	Status
    A	🟢 Alive
    B	🔴 Down
    C	🟢 Alive
    Requests → A, C, A, C … (B ignored)

    class LoadBalancer {
    private:
        vector<Server> servers;
        int index = 0;

    public:
        void addServer(Server server) {
            servers.push_back(server);
        }

        Server getNextServer() {
            Server chosen = servers[index];
            index = (index + 1) % servers.size();
            return chosen;
        }
    };

    LoadBalancer lb;
    lb.addServer(Server("A"));
    lb.addServer(Server("B"));
    lb.addServer(Server("C"));
    lb.getNextServer(); // A
    lb.getNextServer(); // B
    lb.getNextServer(); // C
    lb.getNextServer(); // A again

    consitent hasing for load balance:
        Normal hashing breaks when servers change.
        Consistent hashing survives change by only moving a small set of keys.
        when servers are increased or decresed this will help them

    class ConsistentHashing {
    map<int, string> ring;  // position -> server  
    public:
        void addServer(string serverName) {
            int hashValue = hash(serverName);
            ring[hashValue] = serverName;
        }
        string getServer(string key) {
            int hashValue = hash(key);
            auto it = ring.lower_bound(hashValue);
            if(it == ring.end())
                return ring.begin()->second; // wrap around
            return it->second;
        }
    };

    ConsistentHashing ch;
    ch.addServer("A");
    ch.addServer("B");
    ch.addServer("C");
    cout << ch.getServer("User7"); // maybe "B"

==================================================================================================================================================
CAP theorem tells us:

In a distributed system, you can only guarantee 2 out of 3 things at the same time, not all 3.
The three things are:
Letter	Meaning
C — Consistency	Everyone sees the same data at the same time
A — Availability	System always responds, even if some parts fail
P — Partition Tolerance	System still works even if network breaks between servers

## Partition Tolerance Is Mandatory
We always have P.
So real systems choose (C + P) OR (A + P).

(c+p)=🧠 CP (Consistency + Partition Tolerance)
System prefers accurate data > availability
eg:-Banking, stock trading, SQL clusters
(a+p)=⚡ AP (Availability + Partition Tolerance)
System prefers working fast even if data is temporarily different
eg:-Instagram likes, messaging apps, NoSQL systems

When correctness must be guaranteed → CP.
When speed and uptime is priority → AP.

DATA SHARDING uses the concept of CAP therom

What Is Sharding?
👉 Sharding means splitting a large database into smaller pieces (called shards) so data is stored and processed more efficiently.
Instead of one giant DB doing all work, you divide data across multiple DBs.

Imagine you have 10,000 exam papers and only ONE teacher checking.
She will take days 😭
So you divide papers among 5 teachers:
| Teacher | Papers          |
| ------- | --------------- |
| A       | Roll 1–2000     |
| B       | Roll 2001–4000  |
| C       | Roll 4001–6000  |
| D       | Roll 6001–8000  |
| E       | Roll 8001–10000 |
Now all work happens in parallel → much faster. 
This division = sharding.(if failure occurs use master-slave solution)
=======================================================================================================================================================
What Is a Message Queue?
👉 A Message Queue is a system that stores messages and delivers them asynchronously from one service to another.
In simple words:
One service sends a message → Queue stores it → Another service processes it later.

| Term                          | Meaning                                  |
| ----------------------------- | ---------------------------------------- |
| **Producer**                  | Service that *sends* messages            |
| **Queue**                     | Temporary storage                        |
| **Consumer**                  | Service that *reads/processing* messages |
| **Broker**                    | The queue system (RabbitMQ, Kafka, SQS)  |
| **Acknowledgment**            | Consumer confirms message processed      |
| **Retry / Dead-letter queue** | Failed messages stored here              |
Producer → Send Message → Queue stores → Consumer pulls → Processes → Sends ACK → Removes message

A broker handles communication between services(Kafka ).

In simple terms, when we make a request to the server, the request is added to a message queue. A notifier component monitors server health by sending signals every 10 seconds—if a server doesn't respond, it's assumed to be dead. The notifier checks the database to see if the work is completed and marks it as done. If a server fails, the notifier verifies in the database whether the request was completed. If not, a load balancer assigns the request to another available server to complete the work.

========================================================================================================================================================
Monolithic Architecture
👉 Everything (UI, business logic, database logic, API, payments, notifications, authentication etc.) is inside one single application/codebase.
Imagine a big restaurant with:
Chefs
Cashier
Waiters
Cleaning staff
Delivery staff
BUT…
They are all locked in one room and must work together.
If one person is slow → everyone gets delayed.

Microservices Architecture
👉 Application is broken into small independent services that communicate over network.
Each service has:
Its own logic
Its own deployment
Often its own database

eg:-Same restaurant, but:
    Chefs work in kitchen
    Cashier works separately
    Delivery staff separate team
    Cleaning separate team
    Each group has their own responsibility.
    ✔ If delivery team fails → kitchen still works
    ✔ Teams scale independently (hire more delivery guys if demand grows)

| Area          | Monolith               | Microservices                                  |
| ------------- | ---------------------- | ---------------------------------------------- |
| Framework     | Django, Laravel, Rails | Spring Boot, FastAPI, Go, Node services        |
| DB            | Single MySQL/Postgres  | Many DBs (Mongo, Redis, Cassandra, PostgreSQL) |
| Communication | Function calls         | REST, gRPC, Kafka, RabbitMQ                    |
| Deployment    | One EC2 server         | Kubernetes / Docker                            |

===============================================================================================================================================
What is Cache?
👉 Cache = fast temporary storage used to store frequently accessed data so we don’t repeatedly hit slow backend systems (like DB).
Cache = “Shortcut memory” for your system.

Imagine you are a teacher.
Student repeatedly asks: “Ma’am what is today’s date?”
Instead of telling every time by checking the calendar…
You write the date on the board.
Now 100 students can read it instantly.
That board = cache.

Why Caching in Distributed Systems?
Because:
    DB queries are slow
    Network latency exists
    Millions of users may request the same data

Types of Cache in DS
    1️⃣ Local Cache (In-App Cache)
    Stored in the application's RAM.'
    User → Service → Local Cache → (maybe DB)
    ✔ Very fast
    ❌ Not shared across servers
    ❌ Inconsistent in multi-server architecture
    Example: In-memory maps like Guava Cache, Caffeine.
    
    2️⃣Distributed Cache (Shared Cache)
    All servers use the same cache store.
    Server A ───┐
    Server B ───┼──→ Redis / Memcached
    Server C ───┘
    ✔ Consistent
    ✔ Shared
    ✔ Highly scalable
    Examples: Redis, Memcached, Hazelcast

    3️⃣ CDN Cache (Global Edge Cache)
    Used for static content:
    Images
    JS/CSS
    Videos
    CDN puts data closer to users geographically.
    Example: Netflix distributing videos.

    for more idea or diagram just vist the file 6.system_design_pattern.drawio
=====================================================================================================================================================
What is a CDN?
👉 CDN (Content Delivery Network) is a globally distributed network of servers that deliver content (images, videos, CSS, JS, PDFs, etc.) to users from the nearest location for faster access.
Short version:
Instead of fetching content from the origin server far away, CDN serves it from a nearby server to reduce load time.

Imagine one ice cream factory in Delhi serving all India.
Someone in Kerala orders ice cream.
❌ It will take hours → ice cream melts
❌ Customer becomes angry 😭
So factory creates small ice cream storage shops in:
Kerala
Bangalore
Mumbai
Kolkata
Chennai
Now users get ice cream instantly from nearest store 🍦⚡
Those storage shops = CDN Edge Servers

workflow:-
    User Request → CDN Node Nearby → (If cached: return immediately)
                                   |
                                   ↓
                             If not cached → Origin Server → Cache → Return
in CDN generally only static files are added(image,files,html,css,apis,videos)

           ORIGIN SERVER (Main source)
                        |
                        ↓
             ┌─────────────────────────┐
             │ CONTENT DELIVERY NETWORK │
             └─────────────────────────┘
            /               |                 \
     Edge Server Asia   Edge Server Europe  Edge Server US
         ↓                   ↓                  ↓
  Users in India      Users in Germany     Users in Florida
  get data faster     get data faster      get data faster
