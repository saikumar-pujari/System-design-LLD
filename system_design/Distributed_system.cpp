# Distributed Systems - Complete Guide

## Table of Contents
1. [Introduction to Distributed Systems](#1-introduction-to-distributed-systems)
2. [Scaling Strategies](#2-scaling-strategies)
3. [Performance Metrics](#3-performance-metrics)
4. [System Communication](#4-system-communication)
5. [Load Balancing](#5-load-balancing)
6. [Caching](#6-caching)
7. [Content Delivery Networks (CDN)](#7-content-delivery-networks-cdn)
8. [Databases in Distributed Systems](#8-databases-in-distributed-systems)
9. [Data Sharding](#9-data-sharding)
10. [Replication](#10-replication)
11. [Consistency Models](#11-consistency-models)
12. [CAP Theorem](#12-cap-theorem)
13. [Message Queues](#13-message-queues)
14. [Event-Driven Architecture](#14-event-driven-architecture)
15. [Distributed Transactions](#15-distributed-transactions)
16. [Architecture Patterns](#16-architecture-patterns)
17. [Availability Patterns](#17-availability-patterns)

---

## 1. Introduction to Distributed Systems

### What Is a Distributed System?

A **Distributed System** is a collection of independent computers that work together to appear as a single unified system to the end user.

**Key Characteristics:**
- Multiple machines (nodes/servers) collaborate
- Users perceive it as ONE system
- Transparent operation (complexity is hidden)

### Real-World Analogy: Restaurant Kitchen

Imagine a busy restaurant:
- **Host** takes orders at the front
- **Chef** prepares the food in the kitchen
- **Sous chef** handles appetizers
- **Server** delivers food to tables

To the customer → It feels like ONE seamless dining experience, not four separate people working independently.

**That's a distributed system!**

---

### Why Do We Need Distributed Systems?

| Need | Explanation | Real Example |
|------|-------------|--------------|
| **Scalability** | One machine cannot handle millions of concurrent users | Facebook serving 3 billion users |
| **Fault Tolerance** | System continues working even if components fail | Netflix streaming during server outages |
| **Performance** | Work is distributed and processed in parallel | Google Search returning results in milliseconds |
| **High Availability** | Service remains accessible 24/7 | Banking apps working around the clock |
| **Geographic Distribution** | Serve users from nearby locations | Amazon warehouses across continents |

---

### Core Features of Distributed Systems

| Feature | Description | Example |
|---------|-------------|---------|
| **Decentralization** | No single point of control | Bitcoin blockchain |
| **Replication** | Data exists in multiple copies | Your Gmail stored in 3+ data centers |
| **Consistency Management** | Keeping all copies synchronized | Bank account balance updates |
| **Network Communication** | Machines communicate via HTTP, RPC, gRPC | Microservices talking to each other |
| **Transparency** | Users don't see underlying complexity | YouTube feels like one platform |

### Pizza Chain Analogy

Think of Domino's Pizza:

**Problem:** One store in Mumbai cannot serve customers in Delhi, Bangalore, and Kolkata.

**Solution:** Open multiple branches across cities.

Each branch:
- ✅ Follows the same menu
- ✅ Uses the same pricing
- ✅ Maintains the same quality standards
- ✅ Shares the same brand identity

To customers → It looks like ONE Domino's brand, but it's actually a distributed network of independent stores working together.

---

## 2. Scaling Strategies

### What Is Scalability?

**Scalability** means a system's ability to handle increased load by adding resources, with performance improving proportionally.

**Key Question:** If we double resources, does performance double?

### Types of Scaling

#### Vertical Scaling (Scaling UP) 🏗️

**Definition:** Increase the power of a single machine.

**What You Upgrade:**
- More powerful CPU
- Additional RAM
- Larger storage
- Better GPU

**Analogy:** Your phone is slow → You buy a newer, more powerful phone instead of buying multiple phones.

**Pros:**
- ✅ Simple to implement
- ✅ No code changes needed
- ✅ No distributed complexity

**Cons:**
- ❌ Hardware limits (you can't' infinitely upgrade)
- ❌ Expensive beyond a point
- ❌ Single point of failure

**Example:** Upgrading your laptop from 8GB RAM → 32GB RAM

---

#### Horizontal Scaling (Scaling OUT) 🔗

**Definition:** Add more machines instead of upgrading one.

**Analogy:** Instead of hiring one superhuman worker, hire 10 normal workers who collaborate.

**Pros:**
- ✅ Nearly unlimited scaling potential
- ✅ Better fault tolerance
- ✅ Cost-effective at scale

**Cons:**
- ❌ Requires coordination between machines
- ❌ Data consistency challenges
- ❌ More complex architecture

**Example:** Netflix uses thousands of servers instead of one supercomputer.

**💡 Pro Tip:** Start with vertical scaling for simplicity, then move to horizontal scaling as your user base grows.

---

### Scalability Patterns

| Pattern | Description | Use Case |
|---------|-------------|----------|
| **Partitioning** | Split data across multiple databases | Large user base |
| **HTTPS Caching** | Store responses to avoid recomputation | Static content |(reverse proxy,CDN)
| **RDBMS Sharding** | Divide relational database into chunks | High write loads |
| **NoSQL** | Use non-relational databases for flexibility | Unstructured data |
| **Distributed Caching** | Share cache across servers | Session storage |
| **Concurrency** | Handle multiple requests simultaneously | Real-time apps |

---

## 3. Performance Metrics

### Latency ⏱️

**Definition:** The time it takes for a request to travel from client to server and back.

**Think of it as:** Network delay, ping, or lag.

**Components:**
```
Total Latency = Queue Latency + Server Processing Time
```

**Types of Latency:**

| Type | Description | Example |
|------|-------------|---------|
| **Network Latency** | Time to travel across network | 50ms to reach server |
| **Queue Latency** | Waiting time in request queue | 10 requests ahead of you |
| **Processing Latency** | Time server takes to compute | Database query takes 100ms |

**Performance Formula:**
```
Latency = Server Thread Time / Request Rate

If Latency < Rate Limit → Good Performance ✅
If Latency > Rate Limit → Queue builds up ❌
```

**Example:**
- Sending a message on WhatsApp takes 200ms
- That 200ms = network travel + server processing + return journey

---

### Throughput 📊

**Definition:** The number of requests a system can handle per unit of time.

**Formula:**
```
Throughput = Requests Processed / Time Period
```

**Example:**
- A server processes 1,000 requests per second
- Throughput = 1,000 req/s

**Latency vs Throughput:**
- **Latency:** How fast one request completes
- **Throughput:** How many requests complete in a time window

**Analogy:**
- **Latency:** How fast one car crosses a bridge
- **Throughput:** How many cars cross the bridge per hour

---

### Rate Limiting 🚦

**Definition:** A control mechanism that limits the number of requests a client can make within a specific timeframe.

**Purpose:**
- Prevent system overload
- Protect against DDoS attacks
- Ensure fair resource distribution

**Common Limits:**
- 100 requests per minute
- 1,000 requests per hour
- 10,000 requests per day

**Example:**
Twitter API allows 300 requests per 15-minute window. If you exceed this, you get rate-limited and must wait.

---

## 4. System Communication

### DNS Lookup 🌐

**Definition:** The process of translating human-readable domain names into IP addresses.

**Workflow:**
```
Client: "www.google.com" 
    ↓
1. Check local cache
    ↓
2. Ask DNS Resolver
    ↓
3. Query Root Server: "Where is .com?"
    ↓
4. Query TLD Server: "Where is google.com?"
    ↓
5. Query Authoritative Server: "What is google.com's IP?"
    ↓
Return: "142.250.192.46"
```

**DNS Resolution Types:**

| Type | Description |
|------|-------------|
| **Recursive** | DNS resolver does all work and returns final answer |
| **Iterative** | Resolver returns best known answer, client continues querying |

**Key DNS Components:**

| Component | Role |
|-----------|------|
| **Root Server** | Directs to TLD servers |
| **TLD Server** | Handles top-level domains (.com, .org) |
| **Authoritative Server** | Holds actual domain records (CNAME, A records) |
| **DNS Cache** | Stores recent lookups for faster access |

---

### Proxy Servers 🔄

**Definition:** An intermediary server that sits between clients and backend servers, forwarding requests and responses.

**Types:**

#### Forward Proxy (Client-Side)
```
Client → Forward Proxy → Internet → Server
```
**Use Cases:**
- Hide client identity
- Bypass geographic restrictions
- Content filtering

#### Reverse Proxy (Server-Side)
```
Client → Internet → Reverse Proxy → Backend Servers
```
**Use Cases:**
- Load balancing
- SSL termination
- Caching
- Security (hide backend servers)

**Popular Tools:** Nginx, HAProxy, Apache

---

## 5. Load Balancing

### What Is Load Balancing?

**Definition:** The technique of distributing incoming network traffic across multiple servers to ensure no single server becomes overwhelmed.

**Core Concept:** Use **consistent hashing** to distribute load evenly.

**Formula:**
```
Load per server = Total Load / Number of Servers
Server assignment = Hash(User ID) % Number of Servers
```

**Simple Analogy:**

Imagine a bank with one cashier handling 100 customers.

**Problem:** Long queues, frustrated customers, overworked cashier.

**Solution:** Open 5 cashier counters and distribute customers evenly.

**That distribution mechanism = Load Balancer**

---

### Load Balancer Architecture

```
                    Internet
                       ↓
              [Load Balancer]
                       ↓
        ┌──────────────┼──────────────┐
        ↓              ↓              ↓
   [Server A]     [Server B]     [Server C]
        ↓              ↓              ↓
   [Database]     [Database]     [Database]
```

**Key Features:**
- SSL termination (handles HTTPS encryption)
- Session persistence (sticky sessions)
- Health checks (removes unhealthy servers)
- Cookie management

---

### Load Balancing Layers

#### Layer 4 Load Balancing (Transport Layer)

**Works at:** TCP/UDP level

**Decision Based On:**
- Source IP
- Destination IP
- Port numbers

**Characteristics:**
- ⚡ Very fast
- 🔒 Cannot inspect request content
- 📦 Works with any protocol

**Example:** Distributing based on client IP address.

---

#### Layer 7 Load Balancing (Application Layer)

**Works at:** HTTP/HTTPS level

**Decision Based On:**
- URL path
- HTTP headers
- Request body
- Cookies

**Characteristics:**
- 🧠 Smart routing decisions
- 🔍 Can inspect request content
- 🎯 Route based on content type

**Example:**
```
/api/video/* → Video Processing Servers
/api/payment/* → High-Security Servers
/api/general/* → General Servers
```

**💡 Layer 7 is more powerful but slightly slower than Layer 4.**

---

### Load Balancing Algorithms

#### 1️⃣ Round Robin

**How It Works:** Distribute requests sequentially in a circular manner.

```
Request Flow: A → B → C → A → B → C → A...
```

**Example:**

| Request | Assigned Server |
|---------|----------------|
| Request 1 | Server A |
| Request 2 | Server B |
| Request 3 | Server C |
| Request 4 | Server A |
| Request 5 | Server B |

**Best For:**
- ✅ Servers with equal capacity
- ✅ Similar request processing times
- ✅ Simple setup

**Drawback:**
- ❌ Doesn't consider server load
- ❌ All servers treated equally

---

#### 2️⃣ Weighted Round Robin

**How It Works:** Servers with higher capacity receive proportionally more requests.

**Configuration:**
- Server A (16GB RAM): Weight = 3
- Server B (8GB RAM): Weight = 2
- Server C (4GB RAM): Weight = 1

**Distribution Pattern:**
```
A, A, A, B, B, C, A, A, A, B, B, C...
```

**Best For:**
- ✅ Heterogeneous server hardware
- ✅ Servers with different capabilities
- ✅ API gateways with varying backend capacity

---

#### 3️⃣ Least Connections

**How It Works:** New requests go to the server with the fewest active connections.

**Example Scenario:**

| Server | Active Connections | Next Request? |
|--------|-------------------|---------------|
| Server A | 45 | ❌ |
| Server B | 12 | ✅ (Winner) |
| Server C | 28 | ❌ |

**Formula:**
```
Selected Server = min(Active Connections across all servers)
```

**Best For:**
- ✅ Chat applications
- ✅ Video streaming
- ✅ Long-lived connections
- ✅ WebSocket connections

**Why It Works:**
Requests with varying duration (some take 1 second, others take 10 minutes) need dynamic balancing.

---

#### 4️⃣ IP Hash

**How It Works:** Use client's IP address to consistently route to the same server.

**Formula:**
```
Server = Hash(Client IP) % Number of Servers
```

**Example:**
```
Client IP: 192.168.1.100
Hash: 8547
Servers: 3
Assignment: 8547 % 3 = 0 → Server A

Every time this client connects → Always Server A
```

**Best For:**
- ✅ Session-based applications
- ✅ Shopping carts
- ✅ Gaming servers
- ✅ Sticky sessions

**Benefit:**
User's data stays on one server (session persistence without external storage).

---

#### 5️⃣ Least Response Time

**How It Works:** Route to the server with the fastest response time and fewest connections.

**Decision Formula:**
```
Score = Response Time × Active Connections
Selected Server = min(Score)
```

**Best For:**
- ✅ Performance-critical applications
- ✅ APIs with SLA requirements
- ✅ Real-time services

---

#### 6️⃣ Health-Based (Failover)

**How It Works:** Continuously monitor server health and skip unhealthy servers.

**Health Check Methods:**
- Send heartbeat every 10 seconds
- Check HTTP response status
- Verify service availability

**Example:**

| Server | Status | Receives Traffic? |
|--------|--------|-------------------|
| Server A | 🟢 Healthy | ✅ Yes |
| Server B | 🔴 Down | ❌ No |
| Server C | 🟢 Healthy | ✅ Yes |

**Traffic Flow:**
```
Requests → A, C, A, C, A, C...
(Server B is automatically excluded)
```

---

### Consistent Hashing

**Problem with Regular Hashing:**

When servers are added or removed, most keys get remapped:
```
Server 1, 2, 3 → Add Server 4 → 75% of keys change servers ❌
```

**Consistent Hashing Solution:**

Maps both servers and keys onto a circular hash ring. When servers change, only a small portion of keys get remapped.

```
Visualization:

         Server A
            ↓
     ◀──────●──────▶
     ↑             ↑
Server C          Server B
     ●             ●

Keys between C and A → Go to A
Keys between A and B → Go to B
Keys between B and C → Go to C
```

**Benefits:**
- ✅ Minimal disruption when scaling
- ✅ Only ~K/N keys remapped (K = total keys, N = servers)
- ✅ Graceful degradation

**Use Cases:**
- Distributed caches (Redis, Memcached)
- CDN edge server selection
- Database sharding

---

## 6. Caching

### What Is Caching?

**Definition:** Storing frequently accessed data in fast temporary storage to avoid repeatedly fetching from slower sources.

**Simple Analogy:**

You're a student studying for exams.

**Without Cache:**
Every time you need a formula → Walk to the library → Find the book → Read the formula → Walk back.

**With Cache:**
You write important formulas on sticky notes on your desk. Now you just glance at the notes instantly.

**Those sticky notes = Cache**

---

### Why Cache in Distributed Systems?

| Challenge | How Cache Helps |
|-----------|-----------------|
| Slow database queries | Store results in memory |
| Network latency | Reduce trips to backend |
| Expensive computations | Store computed results |
| High traffic | Serve from cache instead of DB |

**Performance Impact:**
```
Database Query: ~100ms
Cache Hit: ~1ms

100x faster! ⚡
```

---

### Cache Hierarchy

```
Fastest → CPU Cache (L1, L2, L3)
   ↓
Application Memory Cache (In-Process)
   ↓
Distributed Cache (Redis, Memcached)
   ↓
Database Query Cache
   ↓
Slowest → Disk Storage
```

---

### Types of Caching

#### 1️⃣ Client-Side Caching

**Location:** User's browser or device

**What Gets Cached:**
- Images
- CSS/JavaScript files
- HTML pages
- API responses

**Example:**
When you revisit Amazon.com, your browser loads images from local storage instead of re-downloading.

---

#### 2️⃣ Application/In-Memory Cache

**Location:** Within the application's RAM

**Tools:** Guava Cache, Caffeine, In-memory maps

**Architecture:**
```
User Request → Application Server → Local Memory Cache
                                           ↓
                                    (If miss → Database)
```

**Pros:**
- ⚡ Extremely fast (nanoseconds)
- 🔒 No network overhead

**Cons:**
- ❌ Not shared across servers
- ❌ Data inconsistency in multi-server setups
- ❌ Lost on server restart

**Best For:**
- Single-server applications
- Configuration data
- Session storage (single instance)

---

#### 3️⃣ Distributed Cache

**Location:** Separate cache servers shared by all application servers

**Popular Tools:** Redis, Memcached, Hazelcast

**Architecture:**
```
App Server A ──┐
App Server B ──┼──→ [Redis Cluster]
App Server C ──┘
```

**Pros:**
- ✅ Shared across all servers
- ✅ Consistent data
- ✅ Highly scalable
- ✅ Survives app server restarts

**Cons:**
- ❌ Network latency (still much faster than DB)
- ❌ Additional infrastructure

**Best For:**
- Multi-server applications
- Session management
- Real-time leaderboards
- Rate limiting counters

---

### Caching Strategies

#### Write-Through Cache

**Process:**
```
1. Write to Cache
2. Immediately write to Database
3. Return success
```

**Pros:**
- ✅ Cache always consistent with DB
- ✅ No data loss

**Cons:**
- ❌ Slower writes (double write penalty)

**Example:**
Banking transactions where accuracy is critical.

---

#### Write-Behind (Write-Back) Cache

**Process:**
```
1. Write to Cache
2. Return success immediately
3. Asynchronously write to Database (via queue)
```

**Pros:**
- ✅ Very fast writes
- ✅ Better write throughput

**Cons:**
- ❌ Risk of data loss if cache crashes
- ❌ Temporary inconsistency

**Example:**
Social media likes/reactions where slight delay is acceptable.

---

### Cache Eviction Policies

When cache is full, which items should be removed?

| Policy | Description | Use Case |
|--------|-------------|----------|
| **LRU (Least Recently Used)** | Remove items not accessed for longest time | General purpose |
| **LFU (Least Frequently Used)** | Remove items accessed least often | Content recommendation |
| **FIFO (First In, First Out)** | Remove oldest entries | Simple queues |
| **TTL (Time To Live)** | Remove after expiration time | Session data |
| **Random** | Remove random entries | When pattern unclear |

**Most Common:** LRU (balances recency and efficiency)

---

### Cache Invalidation

**The Hard Problem:** How do you know when cached data is stale?

**Strategies:**

#### 1. Time-Based (TTL)
```
Set cache expiry: 5 minutes
After 5 minutes → Refresh from DB
```

#### 2. Event-Based
```
When database updates → Invalidate related cache keys
```

#### 3. Manual
```
Admin triggers cache clear when needed
```

**Example:**
E-commerce product price:
- Cache for 1 hour (TTL)
- Invalidate immediately when price changes (Event)

---

### Cache Patterns

#### Cache-Aside (Lazy Loading)

```python
def get_user(user_id):
    # Try cache first
    user = cache.get(f"user:{user_id}")
    
    if user is None:  # Cache miss
        # Load from database
        user = database.query(user_id)
        # Store in cache
        cache.set(f"user:{user_id}", user, ttl=3600)
    
    return user
```

**When to use:** Read-heavy workloads

---

#### Read-Through Cache

```
Application → Cache → (Cache handles DB fetch if miss)
```

Cache automatically loads data from database on miss.

---

#### Refresh-Ahead

Proactively refresh cache before expiry.

**Example:**
Popular product pages refreshed every 30 minutes automatically.

---

## 7. Content Delivery Networks (CDN)

### What Is a CDN?

**Definition:** A globally distributed network of servers that delivers static content to users from the nearest geographic location.

**Purpose:** Reduce latency by serving content from nearby servers instead of distant origin servers.

---

### Ice Cream Delivery Analogy

**Problem:**

One ice cream factory in Delhi serves all of India.
- Customer in Chennai orders ice cream
- ❌ Takes 3 days to deliver
- ❌ Ice cream melts
- ❌ Customer angry

**Solution:**

Open ice cream storage centers in:
- Chennai
- Bangalore
- Mumbai
- Kolkata
- Hyderabad

Now customers get ice cream from the nearest center within hours!

**Those storage centers = CDN Edge Servers** 🍦

---

### CDN Architecture

```
        [Origin Server - USA]
                |
                ↓
    [Global CDN Distribution]
         /      |      \
        ↓       ↓       ↓
   [Asia     [Europe]  [South
    Edge]              America
                        Edge]
     ↓         ↓          ↓
  Users in   Users in   Users in
   India    Germany     Brazil
```

---

### CDN Workflow

```
User in India requests image.jpg
        ↓
1. DNS routes to nearest CDN edge (Mumbai)
        ↓
2. Mumbai CDN checks cache
        ↓
3a. Cache HIT → Return image immediately ✅
        ↓
3b. Cache MISS → Fetch from origin → Cache → Return
        ↓
4. Future requests served from cache (fast!)
```

---

### CDN Types

#### Push CDN

**Process:**
```
Developer uploads content → CDN stores globally
Future user requests → Served instantly from CDN
```

**Best For:**
- Static websites
- Infrequently changing content
- Small content volumes

**Example:** Deploying a marketing website

---

#### Pull CDN

**Process:**
```
User requests content → CDN checks cache
Cache MISS → CDN pulls from origin → Caches → Serves
Future requests → Cache HIT (fast)
```

**Best For:**
- High traffic sites
- Large content volumes
- Frequently updated content

**Example:** YouTube videos, Netflix streams

---

### What CDNs Cache

| Content Type | Cacheable? | Why |
|--------------|-----------|-----|
| Images (PNG, JPG) | ✅ Yes | Static |
| Videos (MP4) | ✅ Yes | Large, static |
| CSS/JavaScript | ✅ Yes | Rarely changes |
| HTML Pages | ⚠️ Sometimes | Depends on dynamic content |
| API Responses | ⚠️ Sometimes | If data doesn't change often |
| User-specific data | ❌ No | Dynamic, personalized |

---

### CDN Components

| Component | Description |
|-----------|-------------|
| **Origin Server** | Source of content |
| **CDN Entry Point** | Fetches content from origin |
| **Origin Shield** | Protects origin from traffic spikes |
| **Edge Servers** | Serve content to users |
| **CDN Footprint** | Geographic coverage areas |
| **CDN Selector** | Chooses best CDN (multi-CDN) |

---

### Cache Miss Optimization

**Problem:** High cache miss rate = Poor CDN performance

**Solutions:**

1. **Longer TTL:** Cache content for more time
2. **Predictive Prefetching:** Cache popular content before requested
3. **Origin Shield:** Reduce duplicate origin fetches

**Target Metrics:**
- Cache Hit Ratio: >90%
- Cache Miss Ratio: <10%

---

### Benefits of CDN

| Benefit | Impact |
|---------|--------|
| **Reduced Latency** | Content loads 10x faster |
| **Lower Bandwidth Costs** | Less origin server traffic |
| **Improved Availability** | Content served even if origin down |
| **DDoS Protection** | Edge servers absorb attacks |
| **Global Reach** | Serve users worldwide efficiently |

**Example:** Netflix uses CDN to serve 200+ million subscribers globally with minimal buffering.

IMPORTANT--
    In our architecture, all caching layers are accessed in the following order:
    CDN → Proxy Server (forward/reverse proxy) → Load Balancer → External Cache (Redis) → Database Cache → Database.

    Redis acts as the primary external cache and refreshes data based on TTL. However, if all keys expire at the same time, Redis would attempt to regenerate everything simultaneously, which can overload the system.

    To prevent this “cache stampede,” we use a locking mechanism so that only one request refreshes the expired data while the rest wait or serve stale content. This avoids system crashes.

    Whenever there is a cache miss, the system normally falls back to the database — which is expensive because each lookup requires multiple network hops (e.g., 10 ms to Redis and 30 ms to DB for both request and response cycles).
    To optimize this, we maintain a lightweight bit-array (0s and 1s) between the cache and the database:

    1 → the record definitely exists in the DB, so go fetch it.
    0 → the record does not exist, so instantly return “Not Found” without hitting the DB.
    This drastically reduces unnecessary database lookups and improves latency under heavy load.
    
---

## 8. Databases in Distributed Systems

### Database Types

#### 1️⃣ Relational Databases (SQL)

**Structure:** Organized tables with rows and columns

**Examples:** MySQL, PostgreSQL, Oracle

**Best For:**
- Structured data
- Complex relationships
- ACID compliance needed

**Properties (ACID):**
- **Atomicity:** All or nothing
- **Consistency:** Valid state always
- **Isolation:** Transactions don't interfere
- **Durability:** Committed data persists

**Example Use Case:**
Banking system (accounts, transactions, balances)

---

#### 2️⃣ Document Databases

**Structure:** JSON-like documents

**Examples:** MongoDB, CouchDB

**Best For:**
- Unstructured/semi-structured data
- Flexible schemas
- Rapid development

**Example Document:**
```json
{
  "user_id": "12345",
  "name": "Priya",
  "orders": [
    {"item": "Laptop", "price": 50000},
    {"item": "Mouse", "price": 500}
  ]
}
```

**Query Example:**
```javascript
db.products.find({ qty: { $gt: 5 } })
```

---

#### 3️⃣ Columnar Databases

**Structure:** Data stored by columns instead of rows

**Examples:** Apache Cassandra, HBase

**Best For:**
- Analytics
- Large-scale data processing
- Time-series data

**Why Fast for Analytics:**
Reading one column from 1 billion rows is faster than reading all columns.

---

#### 4️⃣ Key-Value Databases

**Structure:** Simple map (key → value)

**Examples:** Redis, DynamoDB, Riak

**Best For:**
- Caching
- Session storage
- Simple lookups

**Example:**
```
Key: "user:12345:session"
Value: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
```

---

#### 5️⃣ Graph Databases

**Structure:** Nodes and edges (relationships)

**Examples:** Neo4j, ArangoDB

**Best For:**
- Social networks
- Recommendation engines
- Fraud detection

**Example:**
```
// (Priya)-[FRIENDS_WITH]->(Raj)
// (Raj)-[LIKES]->(Pizza)
// (Priya)-[LIKES]->(Pizza)

Query: "Find friends who like the same food"
```

---

#### 6️⃣ Time-Series Databases

**Structure:** Optimized for timestamped data

**Examples:** InfluxDB, TimescaleDB

**Best For:**
- IoT sensor data
- Application metrics
- Stock prices

**Example:**
```
timestamp: 2025-12-10 14:30:00
metric: cpu_usage
value: 78.5%
```

---

#### 7️⃣ Vector Databases

**Structure:** Multi-dimensional vectors

**Examples:** Pinecone, Weaviate, Milvus

**Best For:**
- AI/ML applications
- Semantic search
- Recommendation systems

**How It Works:**
Text → Vector embedding → Store → Find similar vectors

**Example:**
```
"Cat" → [0.2, 0.8, 0.3, ...]
"Kitten" → [0.21, 0.79, 0.31, ...] (similar vector)
```

---

## 9. Data Sharding

### What Is Sharding?

**Definition:** Splitting a large database into smaller, manageable pieces (shards) distributed across multiple servers.

**Why Needed:**
One database cannot handle:
- Billions of rows
- Millions of concurrent writes
- Terabytes of data

---

### Exam Paper Analogy

**Problem:**

One teacher checking 10,000 exam papers alone.
- ❌ Takes weeks
- ❌ Slow results
- ❌ Overworked teacher

**Solution:**

Divide papers among 5 teachers:

| Teacher | Papers | Time |
|---------|--------|------|
| Teacher A | Papers 1-2000 | 2 days |
| Teacher B | Papers 2001-4000 | 2 days |
| Teacher C | Papers 4001-6000 | 2 days |
| Teacher D | Papers 6001-8000 | 2 days |
| Teacher E | Papers 8001-10000 | 2 days |

**Result:** All papers checked in 2 days instead of weeks!

**This division = Sharding**

---

### Sharding Strategies

#### 1️⃣ Range-Based Sharding

**Split by:** Data ranges

**Example:**
```
Shard 1: User IDs 1 - 1,000,000
Shard 2: User IDs 1,000,001 - 2,000,000
Shard 3: User IDs 2,000,001 - 3,000,000
```

**Pros:**
- ✅ Simple to implement
- ✅ Easy to add shards

**Cons:**
- ❌ Uneven distribution (hotspots)
- ❌ Some shards busier than others

---

#### 2️⃣ Hash-Based Sharding

**Split by:** Hash function

**Formula:**
```
Shard = Hash(User_ID) % Number_of_Shards
```

**Example:**
```
User 12345 → Hash = 87651 → 87651 % 4 = 3 → Shard 3
```

**Pros:**
- ✅ Even distribution
- ✅ No hotspots

**Cons:**
- ❌ Hard to add/remove shards (requires rehashing)
- ❌ Range queries difficult

---

#### 3️⃣ Geographic Sharding

**Split by:** User location

**Example:**
```
Shard Asia: Users in India, China, Japan
Shard Europe: Users in UK, Germany, France
Shard Americas: Users in USA, Brazil, Mexico
```

**Pros:**
- ✅ Lower latency for users
- ✅ Compliance with data residency laws

**Cons:**
- ❌ Uneven load distribution
- ❌ Complex cross-region queries

---

#### 4️⃣ Directory-Based Sharding

**How It Works:** Lookup table maps keys to shards

**Example:**
```
Lookup Service:
User 123 → Shard A
User 456 → Shard C
User 789 → Shard B
```

**Pros:**
- ✅ Flexible assignment
- ✅ Easy rebalancing

**Cons:**
- ❌ Lookup service is single point of failure
- ❌ Extra network hop

---

### Sharding Challenges

| Challenge | Solution |
|-----------|----------|
| **Cross-Shard Queries** | Denormalization, scatter-gather |
| **Uneven Load** | Rebalancing, consistent hashing |
| **Shard Failure** | Replication, backup shards |
| **Transactions Across Shards** | Two-phase commit, sagas |

---

### When to Shard?

**Signals You Need Sharding:**
- ✅ Database > 100GB and growing
- ✅ Write throughput hitting limits
- ✅ Single server CPU/RAM maxed out
- ✅ Query performance degrading

**Start Simple:** Vertical scaling → Read replicas → Then sharding

---

## 10. Replication

### What Is Replication?

**Definition:** Creating and maintaining multiple copies of data across different servers for reliability and availability.

**Purpose:**
- ✅ Fault tolerance (backup if server fails)
- ✅ Higher read throughput (distribute reads)
- ✅ Lower latency (serve from nearest replica)

---

### Instagram Photo Analogy

When you upload a photo to Instagram:

```
Your Photo → Stored in:
    - Mumbai Server (Primary)
    - Singapore Server (Replica 1)
    - USA Server (Replica 2)
```

**Why?**
- If Mumbai server crashes → Photo still available from Singapore/USA
- Users in Asia → Served from Singapore (fast)
- Users in America → Served from USA (fast)

---

### Replication Models

#### 1️⃣ Master-Slave (Primary-Replica)

**Architecture:**
```
        [Master] (Writes)
           ↓
    ┌──────┼──────┐
    ↓      ↓      ↓
[Slave] [Slave] [Slave] (Reads)
```

**Process:**
1. All writes go to Master
2. Master replicates to Slaves
3. Reads distributed across Slaves

**Pros:**
- ✅ Simple to implement
- ✅ Scales reads effectively
- ✅ Clear consistency model

**Cons:**
- ❌ Single point of failure (Master)
- ❌ Write bottleneck (one Master)

**Use Cases:**
- Read-heavy applications
- Analytics dashboards
- Content websites

---

#### 2️⃣ Master-Master (Multi-Master)

**Architecture:**
```
[Master A] ←→ [Master B]
    ↓              ↓
Writes/Reads   Writes/Reads
```

**Process:**
1. Both nodes accept writes
2. Changes synchronized between masters
3. Reads from any master

**Pros:**
- ✅ No single point of failure
- ✅ Higher write throughput
- ✅ Better availability

**Cons:**
- ❌ Complex conflict resolution
- ❌ Consistency challenges

**Conflict Example:**
```
User A updates name to "Priya" on Master A
User B updates name to "Priyanka" on Master B
Which is correct? (Needs resolution strategy)
```

---

#### 3️⃣ Peer-to-Peer Replication

**Architecture:**
```
[Node A] ←→ [Node B]
    ↕          ↕
[Node D] ←→ [Node C]
```

**Process:**
All nodes are equal, replicate to each other

**Example:** Cassandra's ring architecture

---

### Replication Strategies

#### Synchronous Replication

**Process:**
```
1. Write to Master
2. Wait for ALL replicas to confirm
3. Return success to client
```

**Characteristics:**
- ✅ Strong consistency
- ❌ Slower writes (wait for all)
- ❌ Availability impact if replica down

**Use Cases:** Financial transactions, critical data

---

#### Asynchronous Replication

**Process:**
```
1. Write to Master
2. Return success immediately
3. Replicate to slaves in background
```

**Characteristics:**
- ✅ Fast writes
- ✅ Better availability
- ❌ Temporary inconsistency possible

**Use Cases:** Social media, analytics

---

#### Semi-Synchronous Replication

**Process:**
```
1. Write to Master
2. Wait for ONE replica to confirm
3. Return success
4. Other replicas update asynchronously
```

**Characteristics:**
- ⚖️ Balance between consistency and performance

---

## 11. Consistency Models

### What Is Consistency?

**Definition:** The guarantee about when and how replicated data becomes synchronized across servers.

---

### WhatsApp Message Analogy

When you send a WhatsApp message:

1. **Sent** ✓ (your device has it)
2. **Delivered** ✓✓ (recipient's' device received it)
3. **Read** ✓✓ (blue ticks - recipient saw it)

Updates arrive gradually → This is **eventual consistency**

---

### Types of Consistency

#### 1️⃣ Strong Consistency

**Definition:** All reads return the most recent write immediately.

**Guarantee:** After write completes, all subsequent reads see the new value.

**Example:**
```
Time 0: Balance = $100
Time 1: Withdraw $20 (Balance = $80)
Time 2: Check balance → MUST show $80
```

**How Achieved:** Uses TCP with acknowledgments (ACK)

**Cost:** Lower availability, higher latency

**Use Cases:**
- Banking systems
- Stock trading
- Inventory management

---

#### 2️⃣ Eventual Consistency

**Definition:** All replicas will eventually be consistent, but not immediately.

**Guarantee:** Given enough time without writes, all replicas converge to same value.

**Example:**
```
Time 0: Post a photo on Instagram
Time 1: You see it immediately
Time 2: Friend in USA sees it (1 second delay)
Time 3: Friend in Australia sees it (2 seconds delay)
Eventually: Everyone sees the same photo
```

**Cost:** Temporary inconsistency allowed

**Use Cases:**
- Social media likes
- View counts
- Comments
- DNS propagation

---

#### 3️⃣ Weak Consistency

**Definition:** No guarantee when updates will be visible.

**Example:** Live video streaming - some frames may be lost

---

#### 4️⃣ Read-After-Write Consistency

**Definition:** User sees their own writes immediately, but others may see stale data temporarily.

**Example:**
```
You post a comment → You see it immediately
Others → See it after 1-2 seconds
```

**Use Cases:** User-generated content

---

#### 5️⃣ Monotonic Read Consistency

**Definition:** Once you read a value, you'll never read an older value later.

**Example:**
```
Time 1: Read balance = $80
Time 2: Read balance = $70 or $80 or $90 ✅
Time 2: Read balance = $75 (older) ❌ VIOLATION
```

---

### Two Generals' Problem

**Scenario:** Two armies need to coordinate attack, but messengers can be lost.

**Problem:**
```
General A sends: "Attack at dawn"
General B receives, sends: "Acknowledged"
General A receives acknowledgment

But... How does B know A received the acknowledgment?
Infinite ACK loop!
```

**Lesson:** Perfect consistency in distributed systems with unreliable networks is impossible.

**Real-World Impact:** This is why we use TCP (with ACKs) for strong consistency, accepting the availability trade-off.

---

## 12. CAP Theorem

### What Is CAP Theorem?

**CAP Theorem** states: In a distributed system with network partitions, you can only guarantee 2 out of 3 properties.

| Letter | Property |
|--------|----------|
| **C** | Consistency - All nodes see the same data |
| **A** | Availability - System always responds |
| **P** | Partition Tolerance - Works despite network failures |

---

### The Critical Insight

**Partition Tolerance is MANDATORY** in distributed systems (networks can always fail).

Therefore, the real choice is:
- **CP** (Consistency + Partition Tolerance)
- **AP** (Availability + Partition Tolerance)

---

### Restaurant Analogy

Imagine a restaurant chain with two branches:

**Network Partition:** Phone lines between branches are down.

**CP Choice (Consistency Priority):**
```
Branch A gets new menu update
Branch B can't sync due to network failure
Result: Branch B closes temporarily (unavailable)
        Until sync completes, ensure consistency
```

**AP Choice (Availability Priority):**
```
Branch A gets new menu update
Branch B can't sync due to network failure
Result: Both branches stay open (available)
        But serving different menus (inconsistent)
```

---

### CP Systems (Consistency + Partition Tolerance)

**Behavior:** System may refuse requests to maintain consistency.

**Examples:**
- **Banking systems** - Can't show wrong balance
- **HBase** - Consistent distributed database
- **MongoDB (strong consistency mode)** - Ensures data accuracy
- **Zookeeper** - Distributed coordination

**Trade-off:** Some requests may fail or timeout during network issues.

**When to Choose CP:**
- Correctness is critical
- Can tolerate brief downtime
- Financial transactions
- Inventory management

---

### AP Systems (Availability + Partition Tolerance)

**Behavior:** System always responds, even with potentially stale data.

**Examples:**
- **Instagram likes** - Slight delay is acceptable
- **Cassandra** - Always available
- **DynamoDB** - High availability
- **Couchbase** - Distributed JSON database

**Trade-off:** Data may be temporarily inconsistent.

**When to Choose AP:**
- Uptime is critical
- Can tolerate eventual consistency
- Social media
- Shopping carts (with conflict resolution)
- Analytics dashboards

---

### CAP in Practice

**Reality Check:** Most systems offer tunable consistency.

**Example: Cassandra**
```
Write with consistency level:
- ONE (fast, less consistent - AP)
- QUORUM (balanced)
- ALL (slow, consistent - CP)
```

---

## 13. Message Queues

### What Is a Message Queue?

**Definition:** A system that stores messages temporarily and delivers them asynchronously between services.

**Key Concept:** Decouples producers from consumers.

Service A → sends message → Service B receives it(only communication no works as, it does it from sender to reviver no work)


---

### Post Office Analogy

**Without Message Queue:**
```
You write a letter → Must personally deliver to recipient
- What if recipient is busy?
- What if you're busy when they're free?
```

**With Message Queue:**
```
You write letter → Drop in mailbox → Post office holds it → Delivers when recipient available
```

**The mailbox = Message Queue**

---

### Architecture

```
[Producer Service] → [Message Queue] → [Consumer Service]
                         ↓
                   (Stores messages)
                   (Guarantees delivery)
```

---

### Key Components

| Component | Description | Example |
|-----------|-------------|---------|
| **Producer** | Sends messages | Order service |
| **Queue/Topic** | Stores messages | RabbitMQ queue |
| **Consumer** | Processes messages | Email service |
| **Broker** | Manages queue system | Kafka, RabbitMQ |
| **Acknowledgment** | Confirms processing | ACK signal |
| **Dead Letter Queue** | Failed message storage | Error handling |

---

### Message Queue Workflow

```
1. Order Service creates order → Sends message to queue
2. Queue stores: {"order_id": 123, "user": "Priya"}
3. Email Service pulls message from queue
4. Email Service sends confirmation email
5. Email Service sends ACK to queue
6. Queue deletes message (successfully processed)
```

**If Step 4 Fails:**
```
- No ACK sent
- Message stays in queue
- Retry after timeout
- If repeated failures → Move to Dead Letter Queue
```

---

### Queue Monitoring Pattern

**Notifier Component:** Monitors system health

```
Every 10 seconds:
1. Notifier sends heartbeat to all servers
2. Servers respond with health status
3. If server doesn't' respond → Mark as dead
4. Check database: Was work completed?
5. If not completed → Re-queue task
6. Load balancer assigns to healthy server
```

---

### Popular Message Queue Systems

#### 1️⃣ RabbitMQ

**Best For:** Traditional message queuing

**Features:**
- Multiple exchange types
- Routing rules
- Message acknowledgments

---

#### 2️⃣ Apache Kafka

**Best For:** High-throughput event streaming

**Features:**
- Distributed log
- Millions of messages/second
- Data retention
- Event replay capability

**Architecture:**
```
Producers → Kafka Topics (Partitioned) → Consumer Groups
```

**Use Cases:**
- Event sourcing
- Log aggregation
- Real-time analytics

---

#### 3️⃣ AWS SQS

**Best For:** Managed queue service

**Features:**
- Fully managed
- Auto-scaling
- Serverless integration

---

### Benefits of Message Queues

| Benefit | Explanation |
|---------|-------------|
| **Decoupling** | Services don't need to know about each other |
| **Scalability** | Add more consumers to handle load |
| **Reliability** | Messages not lost if consumer is down |
| **Async Processing** | Producer doesn't wait for consumer |
| **Load Leveling** | Smooth traffic spikes |

---

### Real-World Example: E-Commerce Order

```
User places order:

1. Order Service → Queue: {"order": {...}, "action": "process"}
2. Payment Service ← Consumes from queue
3. Payment Service → Queue: {"order": {...}, "action": "ship"}
4. Shipping Service ← Consumes from queue
5. Shipping Service → Queue: {"order": {...}, "action": "notify"}
6. Email Service ← Consumes from queue

Each service independent, scalable, reliable!
```
Task queues:-
    App → sends task → Celery worker executes it(Ask someone to DO something.)
    when ever a user makes a request the task queue handles it in background to return a result
    eg:->when a user orders a pizza(message queue) then the cheif prepares the pizza(task queues)
        2)write a email(task queue will do it in background)

    Tools:-> celery(django),RQ
    celery works->
    user->application(request bank statements)->taskqueue(redis,kafka)<-->celery(performs the task in lifo and return it to the DB as request in background)
---

## 14. Event-Driven Architecture

### What Is Event-Driven Architecture (EDA)?

**Definition:** Systems communicate by publishing and subscribing to events rather than direct requests.

**Key Concept:** "Something happened" → Multiple services react independently.

---

### School Bell Analogy

Imagine a school bell 🔔 rings at 3 PM.

**The bell is the event.**

**Reactions:**
- Students: Stop studying, pack bags
- Teachers: End lectures
- Peon: Opens main gate
- Canteen: Starts preparing snacks
- Security: Manages exit traffic

**Important:** The bell didn't' tell each person what to do. It simply announced an event. Everyone decided their own response.

**This is Event-Driven Architecture!**

---

### Traditional vs Event-Driven

#### Traditional (Request-Response)
```
Order Service → Calls Payment Service
            → Calls Shipping Service
            → Calls Email Service

(Tight coupling, sequential)
```

#### Event-Driven
```
Order Service → Publishes "OrderPlaced" event
    ↓
Payment Service ← Subscribes, processes payment
Shipping Service ← Subscribes, prepares shipment
Email Service ← Subscribes, sends confirmation
Analytics Service ← Subscribes, logs data

(Loose coupling, parallel)
```

---

### Core Components

| Component | Role |
|-----------|------|
| **Event Producer** | Publishes events |
| **Event Broker** | Routes events (Kafka, RabbitMQ, SNS) |
| **Event Consumer** | Subscribes and reacts to events |
| **Event** | Data about something that happened |

---

### Event Structure

```json
{
  "event_type": "OrderPlaced",
  "timestamp": "2025-12-10T14:30:00Z",
  "data": {
    "order_id": "12345",
    "user_id": "98765",
    "amount": 2500,
    "items": [...]
  }
}
```

---

### Publisher-Subscriber Pattern

```
         [Event Broker]
              ↓
        [Topic: Orders]
         /    |    \
        ↓     ↓     ↓
    [Sub 1] [Sub 2] [Sub 3]
   Payment  Shipping  Email
```

**Key Features:**
- Publishers don't know subscribers
- Subscribers don't know publishers
- Dynamic subscription

---

### Benefits of EDA

| Benefit | Explanation |
|---------|-------------|
| **Loose Coupling** | Services independent |
| **Scalability** | Add subscribers easily |
| **Resilience** | One service failure doesn't break others |
| **Real-time Processing** | React to events instantly |
| **Flexibility** | Add new features without changing existing code |

---

### Event-Driven Use Cases

**E-Commerce:**
```
OrderPlaced event →
  - Payment: Charge card
  - Inventory: Reserve items
  - Shipping: Generate label
  - Analytics: Track sale
  - Email: Send confirmation
```

**Social Media:**
```
PostCreated event →
  - Newsfeed: Add to followers' feeds
  - Notification: Alert tagged users
  - Moderation: Check for violations
  - Analytics: Track engagement
```

---

## 15. Distributed Transactions

### The Challenge

**Problem:** How do you update data across multiple services/databases atomically?

**Example:**
```
Transfer $100 from Account A to Account B

Step 1: Deduct $100 from A
Step 2: Add $100 to B

What if Step 1 succeeds but Step 2 fails?
Money disappears! 💸
```

---

### Two-Phase Commit (2PC)

**Definition:** A distributed transaction protocol ensuring all participants commit or all abort.

---

#### Phase 1: Prepare (Voting)

```
Coordinator: "Everyone ready to commit?"
    ↓
Participant A: "Yes, ready" ✅
Participant B: "Yes, ready" ✅
Participant C: "No, error!" ❌
```

---

#### Phase 2: Commit/Abort

```
If all voted YES:
    Coordinator: "Everyone commit!"
    All participants commit ✅

If any voted NO:
    Coordinator: "Everyone abort!"
    All participants rollback ❌
```

---

### 2PC Workflow

```
1. Application starts transaction
2. Coordinator asks all participants to prepare
3. Participants lock resources, vote YES or NO
4. If all YES → Coordinator commits
5. If any NO → Coordinator aborts
6. Participants execute commit/abort
7. Release locks
```

---

### 2PC Issues

| Issue | Problem |
|-------|---------|
| **Blocking** | If coordinator fails, participants wait forever |
| **Performance** | Locks held for entire 2PC duration |
| **Not Partition-Tolerant** | Network split causes issues |

**Verdict:** 2PC prioritizes consistency over availability (CP system)

---

### Saga Pattern

**Definition:** Break long transaction into smaller local transactions with compensating actions.

**Philosophy:** Instead of locking, use compensation if something fails.

---

### Saga Example: E-Commerce Order

#### Forward Flow (Happy Path)
```
1. Order Service: Create order ✅
2. Payment Service: Charge card ✅
3. Inventory Service: Reserve items ✅
4. Shipping Service: Schedule delivery ✅

Success! 🎉
```

#### Compensation Flow (Failure)
```
1. Order Service: Create order ✅
2. Payment Service: Charge card ✅
3. Inventory Service: Reserve items ❌ FAILS

Compensate:
3. Inventory Service: (no action needed)
2. Payment Service: Refund card 💳
1. Order Service: Cancel order ❌

Saga rolled back!
```

---

### Saga Characteristics

**Compensating Actions:**

| Service | Transaction | Compensating Action |
|---------|------------|---------------------|
| Order | Create order | Cancel order |
| Payment | Charge card | Refund payment |
| Inventory | Reserve items | Release items |
| Shipping | Schedule delivery | Cancel shipment |

**Pros:**
- ✅ Better availability (no long locks)
- ✅ Works with network partitions
- ✅ Scales better

**Cons:**
- ❌ Eventual consistency
- ❌ Complex compensation logic
- ❌ Some actions hard to compensate (emails sent)

---

### When to Use What?

| Scenario | Use |
|----------|-----|
| Banking transactions | 2PC |
| Microservices architecture | Saga |
| Need strong consistency | 2PC |
| Need high availability | Saga |
| Compensations possible | Saga |
| Compensations impossible | 2PC |

---

## 16. Architecture Patterns

### Monolithic Architecture

**Definition:** Entire application built as a single unit.

**Components in One Codebase:**
- User Interface
- Business Logic
- Database Access
- Authentication
- Payments
- Notifications

---

### Restaurant Analogy: Monolith

Imagine a restaurant where everyone works in ONE ROOM:
- Chef cooking
- Cashier billing
- Waiter serving
- Cleaner mopping
- Delivery person waiting

**Problems:**
- ❌ If chef is slow → Everyone affected
- ❌ Can't scale kitchen separately
- ❌ Any change requires restarting entire restaurant
- ❌ One bug crashes entire operation

---

### Monolith Characteristics

**Pros:**
- ✅ Simple to develop initially
- ✅ Easy to test (everything together)
- ✅ Straightforward deployment
- ✅ No network overhead

**Cons:**
- ❌ Hard to scale specific parts
- ❌ Slow deployments (must deploy everything)
- ❌ Technology lock-in
- ❌ One bug can crash entire app

**Best For:**
- Small teams
- Simple applications
- MVPs and prototypes

---

### Microservices Architecture

**Definition:** Application split into small, independent services that communicate over a network.

**Each Service:**
- Own codebase
- Own database (often)
- Own deployment
- Own team

---

### Restaurant Analogy: Microservices

Same restaurant, different approach:
- **Kitchen** (separate building) - Food Service
- **Cashier** (front desk) - Payment Service
- **Delivery** (external team) - Logistics Service
- **Cleaning** (contract staff) - Maintenance Service

**Benefits:**
- ✅ If delivery fails → Kitchen still works
- ✅ Hire more delivery staff without affecting kitchen
- ✅ Each team specialized and independent

---

### Microservices Characteristics

**Pros:**
- ✅ Independent scaling (scale what you need)
- ✅ Technology flexibility (different languages per service)
- ✅ Faster deployments (deploy one service)
- ✅ Fault isolation (one service down doesn't' crash all)
- ✅ Team autonomy

**Cons:**
- ❌ Increased complexity
- ❌ Network latency
- ❌ Distributed debugging challenges
- ❌ Data consistency issues
- ❌ Operational overhead (monitoring, logging)

---

### Comparison Table

| Aspect | Monolith | Microservices |
|--------|----------|---------------|
| **Codebase** | Single | Multiple |
| **Deployment** | All at once | Independent |
| **Scaling** | Entire app | Per service |
| **Technology** | One stack | Mix of technologies |
| **Database** | Shared | Per service (typically) |
| **Team Structure** | One team | Multiple teams |
| **Communication** | Function calls | REST/gRPC/Kafka |
| **Testing** | Easier | Complex |
| **Infrastructure** | Simple | Complex (Kubernetes) |

---

### Technology Examples

**Monolith Stack:**
- Django (Python)
- Ruby on Rails
- Laravel (PHP)
- Single PostgreSQL database

**Microservices Stack:**
- Service A: Spring Boot (Java)
- Service B: FastAPI (Python)
- Service C: Go microservice
- Service D: Node.js
- Databases: MongoDB, Redis, PostgreSQL, Cassandra
- Communication: REST, gRPC, Kafka
- Orchestration: Kubernetes, Docker

---

## 17. Availability Patterns

### What Is Availability?

**Definition:** The percentage of time a system is operational and accessible.

**Measurement:**
```
Availability = (Uptime / Total Time) × 100%
```

---

### Availability Levels

| Level | Uptime % | Downtime/Year |
|-------|----------|---------------|
| 99% (Two nines) | 99% | 3.65 days |
| 99.9% (Three nines) | 99.9% | 8.76 hours |
| 99.99% (Four nines) | 99.99% | 52.6 minutes |
| 99.999% (Five nines) | 99.999% | 5.26 minutes |

**Note:** Each additional nine is exponentially harder and more expensive to achieve.

---

### Failover Patterns

#### Active-Passive Failover

**Setup:**
- **Active Server:** Handles all requests
- **Passive Server:** Standby mode, receives heartbeats

```
[Active Server] → Sends heartbeat → [Passive Server]
      ↓                                    ↓
   Handles                            (Standby mode)
   traffic
```

**Failover Process:**
```
1. Active server crashes
2. Passive server detects missed heartbeats
3. Passive promotes itself to active
4. Starts handling traffic
```

**Pros:**
- ✅ Simple setup
- ✅ Resource efficient (passive server idle)

**Cons:**
- ❌ Wasted resources (passive does nothing)
- ❌ Failover takes time (30-60 seconds)

---

#### Active-Active Failover

**Setup:**
Both servers handle traffic simultaneously.

```
[Load Balancer]
    /        \
   ↓          ↓
[Server A]  [Server B]
  Active     Active
```

**Failover Process:**
```
1. Server A crashes
2. Load balancer detects failure
3. Routes all traffic to Server B
4. No promotion needed
```

**Pros:**
- ✅ Better resource utilization
- ✅ Faster failover (instant)
- ✅ Higher throughput

**Cons:**
- ❌ More complex setup
- ❌ Data synchronization challenges

---

### Replication for High Availability

#### Master-Slave Replication

```
[Master Database]
      ↓ (Replication)
  [Slave 1]  [Slave 2]
```

**Availability Benefit:**
If master fails → Promote slave to master

---

#### Master-Master Replication

```
[Master A] ←→ [Master B]
```

**Availability Benefit:**
Either master can handle requests anytime

---

### Heartbeat Mechanism

**Definition:** Regular "I'm alive" signals between servers.

```
Every 10 seconds:
Active Server → "Still alive" → Passive Server

If 3 consecutive heartbeats missed:
Passive Server → Assumes active is dead → Takes over
```

---

### Geographic Redundancy

**Multi-Region Deployment:**

```
      [Global Load Balancer]
         /        |        \
        ↓         ↓         ↓
   [US Region] [EU Region] [Asia Region]
```

**Benefits:**
- ✅ Survives regional outages
- ✅ Lower latency (serve from nearby region)
- ✅ Compliance with data residency

**Example:** Netflix operates in 190+ countries with regional deployments.

---

## Summary: Distributed Systems Journey

### Design Progression

1. **Start Simple:** Monolithic app on single server
2. **Scale Vertically:** Upgrade server hardware
3. **Add Caching:** Reduce database load
4. **Add CDN:** Serve static content globally
5. **Scale Horizontally:** Add more servers + load balancer
6. **Add Replication:** Database read replicas
7. **Introduce Sharding:** Split database across servers
8. **Use Message Queues:** Decouple services
9. **Adopt Microservices:** Split into independent services
10. **Implement Monitoring:** Track health, metrics, logs

---

### Key Principles

✅ **Start simple, evolve as needed**
✅ **Measure before optimizing**
✅ **Trade-offs are inevitable (CAP theorem)**
✅ **Design for failure**
✅ **Automate everything**
✅ **Monitor, log, alert**

---

### Final Thoughts

Building distributed systems is about making **informed trade-offs**:
- Consistency vs Availability
- Latency vs Throughput
- Simplicity vs Scalability
- Cost vs Performance

**There's no perfect design—only the right design for your specific needs.**

---

**End of Complete Guide** ✅