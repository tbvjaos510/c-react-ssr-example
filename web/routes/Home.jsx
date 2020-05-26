import React from 'react';
import { Link } from 'react-router-dom';

const Home = () => {
  return <div>
    HomePage!
     <br />
    <Link to="/product/test1">test1 상품</Link>
    <Link to="/lazy">lazy</Link>
  </div>
}

export default React.memo(Home);