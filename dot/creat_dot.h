graph is a struct to describe the graph. it holds a array of the nodes.

int graph2dot(Graph g);
static int node2dot(Graph g);
static int edge2dot(Graph g);
static void print_edge2dot(Graph g,int source, int sink, void *data);
int graph_vertex_count(Graph g);
void
graph_foreach(Graph g, int source,
    void (*f)(Graph g, int source, int sink, void *data),
    void *data);
void
graph_foreach(Graph g, int source,
    void (*f)(Graph g, int source, int sink, void *data),
    void *data)
{
    int i;

    assert(source >= 0);
    assert(source < g->n);

    for(i = 0; i < g->alist[source]->d; i++) {
        f(g, source, g->alist[source]->list[i], data);
    }
}

static void print_edge2dot(Graph g,int source, int sink, void *data)
{
    fprintf(stdout,"%d->%d;\n",source,sink);
}

static int edge2dot(Graph g)
{
    assert( NULL);
    int idx = 0;
    int node_cnt = graph_vertex_count(g);
    for(idx = 0;idx<node_cnt; idx++)
    {
        graph_foreach(g,idx,print_edge2dot,NULL);
    }
    return 0;
}

static int node2dot(Graph g)
{
    assert(g != NULL);
    return 0;
}
int graph2dot(Graph g)
{
    fprintf(stdout,"digraph{");
    node2dot(g);
    edge2dot(g);
    fprintf(stdout,"}\n");
    return 0;
}
