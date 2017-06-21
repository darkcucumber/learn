import Control.Monad
import Data.List
import Debug.Trace

data Point numericType = Point (numericType, numericType) deriving (Show)


powa :: (Eq a, Floating a) => a -> Int -> a 
powa 0 0 = error "0^0 not defined"
powa _ 0 = 1
powa number n = foldl (\acc x -> acc * x) 1 (take n (repeat number))

dist :: Point Float -> Point Float -> Float
dist (Point (x, y)) (Point (x1, y1)) = let res = sqrt( (powa (x1 - x) 2) + (powa (y1 - y) 2 ))
                                            in trace (show (Point(x,y), Point(x1,y1), res)) res
    

distancer :: (Float, Point Float) -> Point Float -> (Float, Point Float)
distancer (num, p1 ) p2 =  trace (show (num,  p1, p2)) res
                             where res = (num + (dist p1 p2), p2)


main = do 
    points <- getLine
    let points' = read points :: Int
    -- print "dupa"
    strings <- sequence (take points' (repeat getLine))
    let splitStrings = map ((\x -> Point (x !! 0, x !! 1)).(\x -> (map (read) x)).(\x -> words x)) strings :: [Point Float]
    print $ (fst (foldl distancer (0, head splitStrings) ( (tail splitStrings) ++ [head splitStrings] ))) 
    -- print $ (powa 0 3)
    -- print strings
    -- print splitStrings
    -- print splitStrings
    -- print (distancer (0, head splitStrings) ((tail splitStrings) !! 0))