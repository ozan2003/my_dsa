mod algorithm
{
    use std::cmp::Ordering;
    use std::fmt::{Display, Result as FmtResult};
    use std::ops::Add;

    #[derive(PartialEq, Eq, Clone, Copy)]
    /// Represents a distance in a directed graph.
    pub enum Dist
    {
        Fin(u32),
        Inf,
    }

    impl PartialOrd for Dist
    {
        fn partial_cmp(&self, other: &Self) -> Option<Ordering>
        {
            Some(self.cmp(other))
        }
    }

    impl Ord for Dist
    {
        fn cmp(&self, other: &Self) -> Ordering
        {
            match (self, other)
            {
                (&Dist::Fin(a), &Dist::Fin(b)) => a.cmp(&b),
                (&Dist::Inf, &Dist::Inf) => Ordering::Equal,
                (&Dist::Fin(_), &Dist::Inf) => Ordering::Less,
                (&Dist::Inf, &Dist::Fin(_)) => Ordering::Greater,
            }
        }
    }

    impl Add for Dist
    {
        type Output = Dist;

        fn add(self, other: Self) -> Self::Output
        {
            match (self, other)
            {
                (Dist::Fin(a), Dist::Fin(b)) => Self::Fin(a + b),
                (Dist::Fin(_) | Dist::Inf, Dist::Inf) | (Dist::Inf, Dist::Fin(_)) => Self::Inf,
            }
        }
    }

    impl Display for Dist
    {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> FmtResult
        {
            match *self
            {
                Dist::Fin(value) => write!(f, "{:>3}", value),
                Dist::Inf => write!(f, "{:>3}", "∞"),
            }
        }
    }

    /// A graph represented as an adjacency matrix.
    pub type Graph<const N: usize> = [[Dist; N]; N];

    /// Computes the shortest paths between all pairs of vertices in a directed
    /// graph using the Floyd-Warshall algorithm[1].
    ///
    /// [1]: https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
    ///
    /// # Arguments
    /// * `a` - A mutable reference to a graph represented as an adjacency
    ///   matrix.
    ///
    /// # Complexity
    /// The algorithm runs in O(N^3) time, where N is the number of vertices in
    /// the graph.
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