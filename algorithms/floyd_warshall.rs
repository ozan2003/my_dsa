mod algorithm
{
    use std::cmp::Ordering;
    use std::fmt::Display;
    use std::ops::Add;

    #[derive(PartialEq, Eq, Clone, Copy)]
    /// Represents a distance in a directed graph.
    pub enum Distance
    {
        Finite(u32),
        Inf,
    }

    impl PartialOrd for Distance
    {
        fn partial_cmp(&self, other: &Self) -> Option<Ordering>
        {
            Some(self.cmp(other))
        }
    }

    impl Ord for Distance
    {
        fn cmp(&self, other: &Self) -> Ordering
        {
            match (self, other)
            {
                (&Distance::Finite(a), &Distance::Finite(b)) => a.cmp(&b),
                (&Distance::Inf, &Distance::Inf) => Ordering::Equal,
                (&Distance::Finite(_), &Distance::Inf) => Ordering::Less,
                (&Distance::Inf, &Distance::Finite(_)) => Ordering::Greater,
            }
        }
    }

    impl Add for Distance
    {
        type Output = Distance;

        fn add(self, other: Self) -> Self::Output
        {
            match (self, other)
            {
                (Distance::Finite(a), Distance::Finite(b)) => Self::Finite(a + b),
                (Distance::Finite(_) | Distance::Inf, Distance::Inf) |
                (Distance::Inf, Distance::Finite(_)) => Self::Inf,
            }
        }
    }

    impl Display for Distance
    {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result
        {
            match *self
            {
                Distance::Finite(value) => write!(f, "{}", value),
                Distance::Inf => write!(f, "Inf"),
            }
        }
    }

    /// A graph represented as an adjacency matrix.
    pub type Graph<const N: usize> = [[Distance; N]; N];

    /// Computes the shortest paths between all pairs of vertices in a directed graph using the Floyd-Warshall algorithm[1].
    /// 
    /// [1]: https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
    /// 
    /// # Arguments
    /// * `a` - A mutable reference to a graph represented as an adjacency matrix.
    /// 
    /// # Complexity
    /// The algorithm runs in O(N^3) time, where N is the number of vertices in the graph.
    pub fn floyd_warshall<const N: usize>(a: &mut Graph<N>)
    {
        for k in 0..N
        {
            for i in 0..N
            {
                for j in 0..N
                {
                    a[i][j] = a[i][j].min(a[i][k] + a[k][j]);
                }
            }
        }
    }
}

fn main()
{
    unimplemented!();
}