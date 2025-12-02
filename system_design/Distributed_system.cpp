# Distributed Systems - Complete Guide

## What Is a Distributed System?

A **Distributed System** is a system where:
- Multiple computers (nodes/servers) work together as one unified system to achieve a common goal
- To the user, it appears as ONE system, not multiple separate components

### Real-World Analogy: Juice Stall

Imagine you're' running a juice stall:
- One person takes orders
- One person cuts fruits
- One person blends
- One person delivers

To the customer → It feels like ONE shop, not four people doing different tasks.

**That's' a distributed system!**

---

## Why Do We Need Distributed Systems?

| Need | Reason |
|------|--------|
| **Scalability** | One machine can't' handle millions of users |
| **Fault Tolerance** | If one server fails, the system continues working |
| **Performance** | Work is processed in parallel → Faster results |
| **High Availability** | Available 24×7 without downtime |

---

## Core Features of Distributed Systems

| Feature | Meaning |
|---------|---------|
| **Decentralization** | No single machine controls everything |
| **Replication** | Data exists in multiple copies |
| **Consistency Handling** | Keep all copies synchronized |
| **Communication** | Machines communicate via network (HTTP, RPC, gRPC) |
| **Transparency** | User doesn't' see the underlying complexity |

### Easy Analogy: Pizza Shop Chain

Imagine Pizza Hut:
- **One store** → OK for 10 customers
- **For 1 million customers** → One store cannot handle

**Solution:** Open multiple branches:
- Bangalore branch
- Kolkata branch
- Mumbai branch

All branches follow:
- ✔ Same menu
- ✔ Same pricing
- ✔ Same system

To the customer → Looks like one Pizza Hut, but actually distributed across multiple locations.

---

## Important Concepts in Distributed Systems

### 1️⃣ Load Balancer

**Purpose:** Decides which server handles which request

Think of it as a gatekeeper deciding which counter is free.

**Example:**
```
User request → Load balancer → Server A or B or C
```

### 2️⃣ Replication

**Purpose:** Same data stored in multiple servers so the system doesn't' fail

**Example:** When you upload a photo to Instagram → It is stored in:
- Mumbai server
- Singapore backup
- US replication

So even if 1 server fails → data remains safe.

### 3️⃣ Sharding (Partitioning)

**Purpose:** Split data into parts to improve performance

**Example:**
- Usernames A–M stored in Database 1
- Usernames N–Z stored in Database 2

### 4️⃣ Consistency

**Purpose:** All servers should agree on the same data

Sometimes systems prioritize speed over consistency (CAP theorem logic).

**Example:** WhatsApp message delivery:
- Shows ✔ (sent)
- Then after a few ms shows ✔✔ (delivered)
- Then after sync shows blue ✔✔ (read)

Updates come gradually → That's' **eventual consistency**.

---

## Scaling Strategies

### Vertical Scaling (Scaling UP)

**Meaning:** Increase the power of a single machine

**What you upgrade:**
- CPU
- RAM
- Storage
- GPU

**Example:** Your laptop lags → You increase RAM from 8GB → 16GB
- Same server, more power

### Horizontal Scaling (Scaling OUT)

**Meaning:** Add more machines instead of upgrading one

Requires distributed coordination and consistency management.

**Example:** Instead of using one supercomputer, use:
- Server 1
- Server 2
- Server 3
- ... all connected via distributed load balancing

**💡 Pro Tip:** Start with vertical scaling, then move to horizontal scaling as users increase.

---

## Load Balancing

### What Is Load Balancing?

**Load balancing** is the technique of distributing incoming requests across multiple servers so no single server gets overloaded (uses consistent hashing).

**Formula:** 
- `X/n = 1/n` (where X is servers and n are users)
- `x1 = m % n` (where m is the user)

**Simple explanation:** Instead of one person doing 100 tasks, divide it among many people so everyone works smoothly.

### Architecture:
```
Client → Load Balancer → Server 1
                      → Server 2
                      → Server 3
```

---

## Types of Load Balancing Algorithms

### 1️⃣ Round Robin

**How it works:** Requests go to servers in order: A → B → C → A → B → C → A…

**Example:**

| Request | Server |
|---------|--------|
| R1 | A |
| R2 | B |
| R3 | C |
| R4 | A |
| R5 | B |
| R6 | C |

**📍 Use when:** All servers have equal power and tasks are similar.

---

### 2️⃣ Weighted Round Robin

**How it works:** Stronger servers (more RAM/CPU) get more load

**Example:**
- Server A weight = 3
- Server B weight = 1

**Distribution:** A, A, A, B, A, A, A, B...

---

### 3️⃣ Least Connections

**How it works:** Assign request to the server with the fewest active users

**Example:**

| Server | Current Connections |
|--------|---------------------|
| A | 10 |
| B | 4 |
| C | 7 |

Next request goes to → **Server B**

**📍 Use in:** Chat apps, video calls where connection duration varies.

---

### 4️⃣ IP Hashing

**How it works:** Same client always goes to the same server using a hashing function

**Useful for:**
- ✔ Session-based apps
- ✔ Gaming servers
- ✔ Sticky sessions (shopping cart)

**Example:**
- User1 IP hashed → Server A
- User2 IP hashed → Server B
- Every time User1 returns → Still Server A

---

### 5️⃣ Health-Based Load Balancing (Failover)

**How it works:** If one server is down, load balancer skips it

**Example:**

| Server | Status |
|--------|--------|
| A | 🟢 Alive |
| B | 🔴 Down |
| C | 🟢 Alive |

Requests → A, C, A, C… (B ignored)

---

## Load Balancing Implementation

### Basic Round Robin (Pseudocode)

```cpp
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

// Usage
LoadBalancer lb;
lb.addServer(Server("A"));
lb.addServer(Server("B"));
lb.addServer(Server("C"));
lb.getNextServer(); // A
lb.getNextServer(); // B
lb.getNextServer(); // C
lb.getNextServer(); // A again
```

---

### Consistent Hashing for Load Balancing

**Why needed:** Normal hashing breaks when servers change. Consistent hashing survives changes by only moving a small set of keys.

**Use case:** When servers are added or removed, this approach minimizes disruption.

```cpp
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

// Usage
ConsistentHashing ch;
ch.addServer("A");
ch.addServer("B");
ch.addServer("C");
cout << ch.getServer("User7"); // maybe "B"
```

---

## CAP Theorem

### What CAP Theorem Tells Us:

In a distributed system, you can only guarantee **2 out of 3** things at the same time, not all 3.

| Letter | Meaning |
|--------|---------|
| **C** — Consistency | Everyone sees the same data at the same time |
| **A** — Availability | System always responds, even if some parts fail |
| **P** — Partition Tolerance | System still works even if network breaks between servers |

### Important Note: Partition Tolerance Is Mandatory

We always have **P** in distributed systems.

So real systems choose: **(C + P) OR (A + P)**

---

### 🧠 CP (Consistency + Partition Tolerance)

**Priority:** System prefers accurate data over availability

**Examples:**
- Banking systems
- Stock trading
- SQL clusters

---

### ⚡ AP (Availability + Partition Tolerance)

**Priority:** System prefers working fast even if data is temporarily inconsistent

**Examples:**
- Instagram likes
- Messaging apps
- NoSQL systems

---

### When to Choose What?

- **When correctness must be guaranteed → CP**
- **When speed and uptime is priority → AP**

**Note:** Data sharding uses the concepts of CAP theorem.

---

## Data Sharding

### What Is Sharding?

**Sharding** means splitting a large database into smaller pieces (called shards) so data is stored and processed more efficiently.

Instead of one giant DB doing all work, you divide data across multiple DBs.

### Real-World Analogy

Imagine you have 10,000 exam papers and only ONE teacher checking.
- She will take days 😭

**Solution:** Divide papers among 5 teachers:

| Teacher | Papers |
|---------|--------|
| A | Roll 1–2000 |
| B | Roll 2001–4000 |
| C | Roll 4001–6000 |
| D | Roll 6001–8000 |
| E | Roll 8001–10000 |

Now all work happens in parallel → Much faster!

**This division = Sharding**

**Note:** If failure occurs, use master-slave solution for recovery.

---

## Message Queue

### What Is a Message Queue?

A **Message Queue** is a system that stores messages and delivers them asynchronously from one service to another.

**In simple words:**
One service sends a message → Queue stores it → Another service processes it later.

### Key Terms

| Term | Meaning |
|------|---------|
| **Producer** | Service that sends messages |
| **Queue** | Temporary storage |
| **Consumer** | Service that reads/processes messages |
| **Broker** | The queue system (RabbitMQ, Kafka, SQS) |
| **Acknowledgment** | Consumer confirms message processed |
| **Retry / Dead-letter queue** | Failed messages stored here |

### Workflow

```
Producer → Send Message → Queue stores → Consumer pulls → Processes → Sends ACK → Removes message
```

A **broker** (like Kafka) handles communication between services.

---

### How It Works in Practice

When we make a request to the server:
1. Request is added to a message queue
2. A **notifier component** monitors server health by sending signals every 10 seconds
   - If a server doesn't' respond → Assumed to be dead
3. Notifier checks the database to see if work is completed and marks it as done
4. If a server fails, notifier verifies in the database whether the request was completed
5. If not completed → Load balancer assigns the request to another available server

---

## Architecture Patterns

### Monolithic Architecture

**Definition:** Everything (UI, business logic, database logic, API, payments, notifications, authentication, etc.) is inside one single application/codebase.

#### Restaurant Analogy

Imagine a big restaurant with:
- Chefs
- Cashier
- Waiters
- Cleaning staff
- Delivery staff

**BUT…** They are all locked in one room and must work together.

**Problem:** If one person is slow → Everyone gets delayed.

---

### Microservices Architecture

**Definition:** Application is broken into small independent services that communicate over a network.

Each service has:
- Its own logic
- Its own deployment
- Often its own database

#### Same Restaurant, Different Approach

- Chefs work in kitchen
- Cashier works separately
- Delivery staff = separate team
- Cleaning = separate team

**Benefits:**
- ✔ If delivery team fails → Kitchen still works
- ✔ Teams scale independently (hire more delivery staff if demand grows)

---

### Comparison: Monolith vs Microservices

| Area | Monolith | Microservices |
|------|----------|---------------|
| **Framework** | Django, Laravel, Rails | Spring Boot, FastAPI, Go, Node services |
| **Database** | Single MySQL/Postgres | Multiple DBs (MongoDB, Redis, Cassandra, PostgreSQL) |
| **Communication** | Function calls | REST, gRPC, Kafka, RabbitMQ |
| **Deployment** | One EC2 server | Kubernetes / Docker |

---

## Caching

### What is Cache?

**Cache** = Fast temporary storage used to store frequently accessed data so we don't' repeatedly hit slow backend systems (like databases).

**Simple definition:** Cache = "Shortcut memory" for your system.

### Teacher Analogy

Imagine you are a teacher.

Student repeatedly asks: "Ma'am, what is today's date?"

Instead of telling every time by checking the calendar… **You write the date on the board.**

Now 100 students can read it instantly.

**That board = Cache**

---

### Why Caching in Distributed Systems?

Because:
- DB queries are slow
- Network latency exists
- Millions of users may request the same data

---

## Types of Cache in Distributed Systems

### 1️⃣ Local Cache (In-App Cache)

**Storage:** In the application's' RAM

**Flow:**
```
User → Service → Local Cache → (maybe DB)
```

**Pros:**
- ✔ Very fast

**Cons:**
- ❌ Not shared across servers
- ❌ Inconsistent in multi-server architecture

**Examples:** In-memory maps like Guava Cache, Caffeine

---

### 2️⃣ Distributed Cache (Shared Cache)

**Storage:** All servers use the same cache store

**Architecture:**
```
Server A ───┐
Server B ───┼──→ Redis / Memcached
Server C ───┘
```

**Pros:**
- ✔ Consistent
- ✔ Shared across all servers
- ✔ Highly scalable

**Examples:** Redis, Memcached, Hazelcast

---

### 3️⃣ CDN Cache (Global Edge Cache)

**Use case:** Static content delivery
- Images
- JS/CSS files
- Videos

**How it works:** CDN puts data closer to users geographically

**Example:** Netflix distributing videos globally

**Note:** For more details and diagrams, visit file: `6.system_design_pattern.drawio`

---

## Content Delivery Network (CDN)

### What is a CDN?

**CDN (Content Delivery Network)** is a globally distributed network of servers that deliver content (images, videos, CSS, JS, PDFs, etc.) to users from the nearest location for faster access.

**Short version:** Instead of fetching content from a far-away origin server, CDN serves it from a nearby server to reduce load time.

### Ice Cream Factory Analogy

Imagine one ice cream factory in Delhi serving all of India.

Someone in Kerala orders ice cream:
- ❌ It will take hours → Ice cream melts
- ❌ Customer becomes angry 😭

**Solution:** Factory creates small ice cream storage shops in:
- Kerala
- Bangalore
- Mumbai
- Kolkata
- Chennai

Now users get ice cream instantly from the nearest store 🍦⚡

**Those storage shops = CDN Edge Servers**

---

### CDN Workflow

```
User Request → CDN Node Nearby → (If cached: return immediately)
                               |
                               ↓
                        If not cached → Origin Server → Cache → Return
```

**Note:** In CDN, generally only static files are cached (images, files, HTML, CSS, APIs, videos)

---

### CDN Architecture

```
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
```

---

## Event-Driven Architecture

### What Is Event-Driven Architecture?

In **EDA**, systems communicate using events instead of direct requests.

**Simple explanation:** Something happens → That event is published → Other services react to it.

### Basic Flow

```
Producer → Event Broker → Consumers
```

### Key Roles

| Role | Meaning |
|------|---------|
| **Producer** | Service that creates/publishes events |
| **Broker** | System that stores and routes events (Kafka, RabbitMQ, SNS, Redis Streams) |
| **Consumer** | Service(s) that process events |

---

### School Bell Analogy

Imagine a school bell 🔔 rings.

**The bell is the event.**

Once the bell rings:
- Students stop class
- Teacher ends lecture
- Peon opens gate
- Canteen prepares lunch

**Important:** The bell didn't tell each person what to do. It just announced an event → Everyone reacted.

**This is an event-driven system!**

**Note:** An event is something that happened in the system.
- **Example:** `OrderPlaced`

---

### Comparing Event-Driven with Publisher-Subscriber Pattern

```
Publisher ---> Broker Topic ---> Subscriber 1
                             ---> Subscriber 2
                             ---> Subscriber 3
```

---

**End of Guide**