import React from 'react';

const Lazy = () => {
  return <div>
    lazy loaded
  </div>
}

export default React.memo(Lazy);