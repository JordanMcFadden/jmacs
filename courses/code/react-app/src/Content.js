const Content = () => {
    const name = "Jordan";
    const handleCarChange = () => {
        const cars = ['Honda', 'Toyota', 'Altima'];
        const int = Math.floor(Math.random() * 3);
        return cars[int];
    }
    return (
	<main>
	  <p>
            Hello {handleCarChange()}!
          </p>
          <p>
            Hello {name}!
          </p>
        </main>
    );
}

export default Content;
