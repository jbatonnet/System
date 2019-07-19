using System;
using System.Collections.Generic;
using System.Linq;

public static class Extensions
{
    public static string Join<T>(this IEnumerable<T> me, string separator = "")
    {
        return string.Join(separator, me);
    }

    public static Dictionary<TKey, TValue> ToDictionary<TKey, TValue>(this IEnumerable<KeyValuePair<TKey, TValue>> me)
    {
        return me.ToDictionary(p => p.Key, p => p.Value);
    }

    public static IEnumerable<TDestination> SelectMany<TSource, TDestination>(this IEnumerable<TSource> me, Func<TSource, IEnumerable<TDestination>> projection, TDestination separator)
    {
        IEnumerator<TSource> enumerator = me.GetEnumerator();

        if (!enumerator.MoveNext())
            yield break;

        foreach (TDestination item in projection(enumerator.Current))
            yield return item;

        while (enumerator.MoveNext())
        {
            yield return separator;

            foreach (TDestination item in projection(enumerator.Current))
                yield return item;
        }
    }

    public static string Before(this string me, string separator)
    {
        int index = me.IndexOf(separator);
        return index == -1 ? me : me.Substring(0, index);
    }
    public static string After(this string me, string separator)
    {
        int index = me.IndexOf(separator);
        return index == -1 ? me : me.Substring(index + separator.Length);
    }
    public static string ToFirstLower(this string me)
    {
        return me.Substring(0, 1).ToLower() + me.Substring(1);
    }
}